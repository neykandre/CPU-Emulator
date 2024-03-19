#include <iostream>
#include "../include/parser.hpp"

namespace cpu_emulator {

    Instruction Parser::getInstruction() {
        if (!in_.is_open()) {
            in_.open(file_path_);
        }

        std::string line;
        std::getline(in_, line);
        file_line_pos_++;
        while (!in_.eof() && line.find_first_not_of(" \t") == std::string::npos) {
            std::getline(in_, line);
            file_line_pos_++;
        }
        if (in_.eof() && line.find_first_not_of(" \t") == std::string::npos) {
            return {.type = commandType::eof};
        }

        std::sregex_iterator start_iter(line.begin(), line.end(), default_pattern_);
        std::sregex_iterator end_iter;
        commandType type = mapped_command_type[start_iter->str()];

        if (type == commandType::unknown) {
            if (start_iter->suffix().length() == 1 && start_iter->suffix().str()[0] == ':') {
                type = commandType::label;
            }
        }

        if (type != commandType::label) {
            start_iter++;
        }

        std::vector<argToken> args;
        for (auto cur_iter = start_iter; cur_iter != end_iter; ++cur_iter) {
            argToken cur_arg;
            std::find_if(mapped_arg_regexes.begin(),
                         mapped_arg_regexes.end(),
                         [cur_iter](auto x) { return std::regex_match(cur_iter->str(), x.first); })
                         ->second(cur_arg, cur_iter->str());
            args.push_back(cur_arg);
        }

        Instruction ret_instruction{.type = type,
                .args = std::move(args),
                .line_pos = file_line_pos_,
                .src_string = line};
        return ret_instruction;
    }

    Parser::Parser(const std::string& path) {
        file_path_ = path;
    }

}