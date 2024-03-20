#include "exceptBuilder.hpp"
#include "../include/parser.hpp"

namespace cpu_emulator {

    std::map<std::string, commandType> Parser::mapped_command_type = {
            {"push",  commandType::push},
            {"pop",   commandType::pop},
            {"pushr", commandType::pushR},
            {"popr",  commandType::popR},
            {"add",   commandType::add},
            {"sub",   commandType::sub},
            {"mul",   commandType::mul},
            {"div",   commandType::div},
            {"out",   commandType::out},
            {"in",    commandType::in},
            {"begin", commandType::begin},
            {"end",   commandType::end},
            {"jmp",   commandType::jump},
            {"jeq",   commandType::jumpEq},
            {"jne",   commandType::jumpNe},
            {"ja",    commandType::jumpGr},
            {"jae",   commandType::jumpGrEq},
            {"jb",    commandType::jumpLes},
            {"jbe",   commandType::jumpLesEq},
            {"ret",   commandType::ret},
            {"call",   commandType::call}
    };

    std::map<std::string, enum_registers> Parser::mapped_registers = {
            {"eax", enum_registers::eax},
            {"ebx", enum_registers::ebx},
            {"ecx", enum_registers::ecx},
            {"edx", enum_registers::edx}
    };

    std::vector<std::pair<std::regex, std::function<void(argToken&, const std::string&)>>> Parser::mapped_arg_regexes = {
            {std::regex(R"(-?\d*\.?\d+)"), [](auto& arg_token, auto& s) {
                arg_token.type = argType::value;
                arg_token.arg = std::stoll(s);
            }},
            {std::regex(R"(e[a-d]x)"),     [](auto& arg_token, auto& s) {
                arg_token.type = argType::reg;
                arg_token.arg = mapped_registers[s];
            }},
            {std::regex(R"(\w+)"),         [](auto& arg_token, auto& s) {
                arg_token.type = argType::label;
                arg_token.label = s;
            }},
            {std::regex(R"(.+)"),          [](auto& arg_token, auto& s) {
                arg_token.type = argType::unknown;
            }}
    };

    Instruction Parser::getInstruction() {
        if (!in_.is_open()) {
            in_.open(file_path_);
            if (!in_.is_open()) {
                    throw ExceptBuilder<no_file>()
                            .setNote("No such file: " + file_path_ + "\n")
                            .get();
            }
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
        return {.type = type,
                .args = std::move(args),
                .line_pos = file_line_pos_,
                .src_string = line};
    }

    Parser::Parser(const std::string& path) {
        file_path_ = path;
    }

}