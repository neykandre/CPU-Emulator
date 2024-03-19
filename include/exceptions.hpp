#pragma once

#include <string>
#include <stdexcept>

namespace cpu_emulator {
    struct preprocess_error : public std::logic_error {
        explicit preprocess_error(const std::string& message)
                : std::logic_error(message),
                  message(message) {}

    protected:
        std::string message;
    };

    struct too_many_args : public preprocess_error {
        using preprocess_error::preprocess_error;
    };

    struct too_few_args : public preprocess_error {
        using preprocess_error::preprocess_error;
    };

    struct unknown_command : public preprocess_error {
        using preprocess_error::preprocess_error;
    };

    struct invalid_argument_type : public preprocess_error {
        using preprocess_error::preprocess_error;
    };

    struct begin_absence : public preprocess_error {
        using preprocess_error::preprocess_error;
    };

    struct end_absence : public preprocess_error {
        using preprocess_error::preprocess_error;
    };

    struct incorrect_order : public preprocess_error {
        using preprocess_error::preprocess_error;
    };

    struct invalid_label : public preprocess_error {
        using preprocess_error::preprocess_error;
    };
}