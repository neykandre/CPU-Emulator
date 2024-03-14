#include "../include/exceptions.hpp"

namespace cpu_emulator {

    preprocess_error::preprocess_error(const std::string& message)
            : std::logic_error(message),
              message_(message) {}

    too_many_args::too_many_args(const std::string& message)
            : preprocess_error(message) {}

    too_few_args::too_few_args(const std::string& message)
            : preprocess_error(message) {}

    unknown_command::unknown_command(const std::string& message)
            : preprocess_error(message) {}

    invalid_argument::invalid_argument(const std::string& message)
            : preprocess_error(message) {}

    begin_absence::begin_absence(const std::string& message)
            : preprocess_error(message) {}

    end_absence::end_absence(const std::string& message)
            : preprocess_error(message) {}

    incorrect_order::incorrect_order(const std::string& message)
            : preprocess_error(message) {}
}