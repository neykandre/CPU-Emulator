#pragma once

#include <string>
#include "../operations/include/operations.hpp"
#include "preprocessor.hpp"
#include "settings.hpp"
#include "state.hpp"

namespace cpu_emulator {
    class Cpu {
    private:
        CpuState state_;
        std::string file_path_;
    public:
        void setFilePath(const std::string&);
        void setFilePath(std::string&&);

        void exec();
    };
}