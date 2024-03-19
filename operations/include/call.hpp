#pragma once

#include "jump.hpp"

namespace cpu_emulator::operations {
    class Call : public Jump {
        using Jump::Jump;

        void doIt(std::shared_ptr<cpu_emulator::CpuState>) override;
    };
}