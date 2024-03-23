#include <iostream>
#include "cpu.hpp"
#include "binSerializer.hpp"

namespace cpu_emulator {
    void Cpu::exec(const std::string& file_path) {
        Preprocessor preprocessor(file_path);
        try {
            preprocessor.process();
        }
        catch (const preprocess_error& e) {
            std::cerr << "PREPROCESS ERROR\n" << std::endl;
            std::cerr << e.what() << std::endl;
            return;
        }
        catch (const no_file& e) {
            std::cerr << "FILE ERROR\n" << std::endl;
            std::cerr << e.what() << std::endl;
            return;
        }

        operations_tape_ = std::move(preprocessor.getOperations());
        ptr_state_->head = preprocessor.getStartPos();
        operations_tape_[ptr_state_->head]->doIt(ptr_state_);
        while (ptr_state_->is_running) {
            ptr_state_->head++;
            operations_tape_[ptr_state_->head]->doIt(ptr_state_);
        }
        operations_tape_.clear();
    }

    void Cpu::execBinary(const std::string& bin_path) {
        try {
            auto head_vec_pair = Serializer::deserialize(bin_path);
            ptr_state_->head = head_vec_pair.first;
            operations_tape_ = std::move(head_vec_pair.second);
        }
        catch (const no_file& e) {
            std::cerr << "DESERIALIZE ERROR\n" << std::endl;
            std::cerr << e.what() << std::endl;
        }

        operations_tape_[ptr_state_->head]->doIt(ptr_state_);
        while (ptr_state_->is_running) {
            ptr_state_->head++;
            operations_tape_[ptr_state_->head]->doIt(ptr_state_);
        }
        operations_tape_.clear();
    }
}