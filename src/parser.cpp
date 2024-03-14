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

        if(in_.eof() && line.find_first_not_of(" \t") == std::string::npos) {
            return {.type = commandType::eof};
        }

        std::regex pattern(R"(\w+)");
        std::sregex_iterator start_iter(line.begin(), line.end(), pattern);
        std::sregex_iterator end_iter;
        commandType type = mapped_command_type[start_iter->str()];

        if (type == commandType::unknown) {
            if (std::regex_match(start_iter->str(), std::regex(R"(\w+:)"))) {
                type = commandType::label;
            }
        }

        if (type != commandType::label) {
            start_iter++;
        }

        std::vector<argToken> args;
        for (auto cur_iter = start_iter; cur_iter != end_iter; ++cur_iter) {
            argToken cur_arg;
            for (size_t type_idx = 1; type_idx != static_cast<size_t>(argType::_count); ++type_idx) {
                auto check_type = static_cast<argType>(type_idx);
                if(std::regex_match(cur_iter->str(), mapped_arg_regexes[check_type])) {
                    cur_arg.type = check_type;
                    switch (cur_arg.type) {
                        case argType::value:
                            cur_arg.arg = std::stoll(cur_iter->str());
                            break;
                        case argType::reg:
                            cur_arg.arg = mapped_registers[cur_iter->str()];
                            break;
                        case argType::label:
                            cur_iter->str().pop_back();
                            cur_arg.arg = cur_iter->str();
                            break;
                    }
                    break;
                }
            }
            args.push_back(cur_arg);
        }

        Instruction ret_instruction;
        ret_instruction.type = type;
        ret_instruction.args = std::move(args);
        ret_instruction.line_pos = file_line_pos_;
        ret_instruction.src_string = line;
        return ret_instruction;
    }

    Parser::Parser(const std::string& path) {
        file_path_ = path;
    }

}