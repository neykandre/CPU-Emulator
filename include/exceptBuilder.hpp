#pragma once

#include "exceptions.hpp"

namespace cpu_emulator {
    template<class T>
    class ExceptBuilder {
    private:
        size_t line_pos_{0};
        std::string src_line_;
        std::string note_;
    public:
        ExceptBuilder& setLineText(const std::string& line) {
            src_line_ = line;
            return *this;
        }

        ExceptBuilder& setLinePos(size_t pos) {
            line_pos_ = pos;
            return *this;
        }

        ExceptBuilder& setNote(const std::string& note) {
            note_ = note;
            return *this;
        }

        const T& get() {
            std::string error_message;
            if (line_pos_) {
                error_message += std::to_string(line_pos_) + " |\t" + src_line_ + "\n";
            }

            error_message += note_;
            return T(error_message);
        }
    };
}