#pragma once

#include <string>
#include <stdexcept>
#include <fstream>
#include <regex>
#include "state.hpp"
#include "token.hpp"

namespace cpu_emulator {

    class Parser {
    private:
        std::string file_path_;
        std::ifstream in_;
        size_t file_line_pos_{0};

        std::regex default_pattern_{std::regex(R"(\w+)")};

        std::map<std::string, commandType> mapped_command_type{
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
                {"ret",   commandType::ret},
                {"begin", commandType::begin},
                {"end",   commandType::end},
                {"jmp", commandType::jump},
                {"jeq", commandType::jumpEq},
                {"jne", commandType::jumpNe},
                {"ja", commandType::jumpGr},
                {"jae", commandType::jumpGrEq},
                {"jb", commandType::jumpLes},
                {"jbe", commandType::jumpLesEq}
        };

        std::map<std::string, enum_registers> mapped_registers{
                {"eax", enum_registers::eax},
                {"ebx", enum_registers::ebx},
                {"ecx", enum_registers::ecx},
                {"edx", enum_registers::edx}
        };

        std::vector<std::pair<std::regex, std::function<void(argToken&, const std::string&)>>> mapped_arg_regexes{
                {std::regex(R"(-?\d*\.?\d+)"),    [](auto& arg_token, auto& s) {
                    arg_token.type = argType::value;
                    arg_token.arg = std::stoll(s);
                }},
                {std::regex(R"(e[a-d]x)"), [&](auto& arg_token, auto& s) {
                    arg_token.type = argType::reg;
                    arg_token.arg = mapped_registers[s];
                }},
                {std::regex(R"(\w+)"),        [](auto& arg_token, auto& s) {
                    arg_token.type = argType::label;
                    arg_token.arg = s;
                }},
                {std::regex(R"(.+)"),         [](auto& arg_token, auto& s) {
                    arg_token.type = argType::unknown;
                }}
        };

    public:

        Parser() = delete;

        Parser(const std::string&); //NOLINT

        Instruction getInstruction();

    };
}