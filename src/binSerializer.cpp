#include <memory>
#include <iostream>
#include "exceptBuilder.hpp"
#include "../include/binSerializer.hpp"
#include "../include/preprocessor.hpp"

namespace cpu_emulator {
    struct Serializer::VisitorWrapper {
        size_t operator()(const std::string&) {
            throw ExceptBuilder<invalid_argument_type>()
                    .setNote("Not size_t convertible type")
                    .get();
        }

        size_t operator()(auto& arg) {
            return static_cast<size_t>(arg);
        }
    };

    void Serializer::serialize(const std::string& src_path) {
        size_t head;
        vec_op operations_tape;
        try {
            Preprocessor preprocessor(src_path);
            preprocessor.process();
            head = preprocessor.getStartPos();
            operations_tape = preprocessor.getOperations();
        }
        catch (const preprocess_error& e) {
            std::cerr << "\nSERIALIZE ERROR" << std::endl;
            std::cerr << e.what() << std::endl;
            return;
        }

        std::string bin_file_name = std::regex_replace(src_path, file_name_regex_, "$&.bin");
        std::ofstream file(bin_file_name, std::ios::binary);

        if(!file.is_open()) {
            throw ExceptBuilder<no_file>()
                    .setNote("Cannot create file in this directory: " + bin_file_name)
                    .get();
        }

        file.write(reinterpret_cast<char*>(&head), sizeof(head));
        for (const auto& operation: operations_tape) {
            commandType type = operation->getInstruction().type;
            file.write(reinterpret_cast<char*>(&type), sizeof(type));
            for (const auto& arg: operation->getInstruction().args) {
                size_t arg_val = std::visit(VisitorWrapper{}, arg.arg);
                file.write(reinterpret_cast<char*>(&arg_val), sizeof(size_t));
            }
        }
    }

    std::pair<size_t, Serializer::vec_op> Serializer::deserialize(const std::string& bin_file) {
        std::ifstream file(bin_file, std::ios::binary);

        if(!file.is_open()) {
            throw ExceptBuilder<no_file>()
                    .setNote("No such file: " + bin_file)
                    .get();
        }

        size_t head;
        file.read(reinterpret_cast<char*>(&head), sizeof(head));

        vec_op operation_tape;

        while (!file.eof()) {
            commandType type;
            file.read(reinterpret_cast<char*>(&type), sizeof(type));
            base_op_ptr new_operation = Preprocessor::makeOperation(type);
            size_t args_num = new_operation->getReqArgsNum();
            std::vector<argToken> args;
            while (args_num--) {
                size_t cur_arg_val;
                file.read(reinterpret_cast<char*>(&cur_arg_val), sizeof(cur_arg_val));
                args.push_back({.type = argType::unknown, .arg = cur_arg_val});
            }
            Instruction i = {.type = type, .args = args};
            new_operation->moveInstruction(i);
            operation_tape.push_back(new_operation);
        }

        return {head, operation_tape};
    }
}