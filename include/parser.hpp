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

        static std::map<std::string, commandType> mapped_command_type;

        static std::map<std::string, enum_registers> mapped_registers;

        static std::vector<std::pair<std::regex, std::function<void(argToken&, const std::string&)>>> mapped_arg_regexes;

    public:

        Parser() = delete;

        Parser(const std::string&); //NOLINT

        Instruction getInstruction();

    };
}