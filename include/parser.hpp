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
                {"end",   commandType::end}
        };

        std::map<argType, std::regex> mapped_arg_regexes{
                {argType::reg,   std::regex(R"(e[a-d]x)")},
                {argType::value, std::regex(R"(-?\d+)")},
                {argType::label, std::regex(R"(\w+:)")}
        };

        std::map<std::string, enum_registers> mapped_registers{
                {"eax", enum_registers::eax},
                {"ebx", enum_registers::ebx},
                {"ecx", enum_registers::ecx},
                {"edx", enum_registers::edx}
        };

    public:

        Parser() = delete;

        Parser(const std::string&); //NOLINT

        Instruction getInstruction();

    };
}