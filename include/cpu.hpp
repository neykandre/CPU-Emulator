#pragma once

#include <string>
#include "../operations/include/operations.hpp"
#include "preprocessor.hpp"
#include "settings.hpp"
#include "state.hpp"

namespace cpu_emulator {
    class Cpu {
    private:
        std::shared_ptr<CpuState> ptr_state_{std::make_shared<CpuState>()};

        std::vector<std::shared_ptr<operations::BaseOperation>> operations_tape_;

    public:

        void exec(const std::string&);

        void execBinary(const std::string&);
    };
}