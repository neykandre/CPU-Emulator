#pragma once

#include <string>
#include <stdexcept>

namespace cpu_emulator {
    struct preprocess_error : public std::logic_error {
        explicit preprocess_error(const std::string&);

    protected:
        std::string message;


    };

    struct too_many_args : public preprocess_error {
        explicit too_many_args(const std::string&);
    };

    struct too_few_args : public preprocess_error {
        explicit too_few_args(const std::string&);
    };

    struct unknown_command : public preprocess_error {
        explicit unknown_command(const std::string&);
    };

    struct invalid_argument : public preprocess_error {
        explicit invalid_argument(const std::string&);
    };

    struct begin_absence : public preprocess_error {
        explicit begin_absence(const std::string&);
    };

    struct end_absence : public preprocess_error {
        explicit end_absence(const std::string&);
    };

    struct incorrect_order : public preprocess_error {
        explicit incorrect_order(const std::string&);
    };
}