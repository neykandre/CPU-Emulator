#pragma once

#include <string>
#include <stdexcept>
#include "state.hpp"
#include "token.hpp"
#include "../operations/include/operationBuilder.hpp"

namespace cpu_emulator {

    struct too_few_args : public std::logic_error {
        explicit too_few_args(size_t, int, std::string&);
    private:
        std::string message;
    };

    struct unknown_command : public std::logic_error {
        explicit unknown_command(const std::string&);

    private:
        std::string message;
    };

    class Parser {
    private:
        std::string file_path_;
        CpuState start_state_;
        std::vector<std::unique_ptr<operations::baseOperation>> operations_tape_;
        bool was_opened_{false};

        ParsedLine parseLine(const std::string&, size_t);

        void parseFile();

    public:

        void setFilePath(const std::string&);

        void setFilePath(std::string&&);

        std::vector<std::unique_ptr<operations::baseOperation>>& getOperations();

    };
}