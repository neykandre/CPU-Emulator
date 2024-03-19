#pragma once

#include "jump.hpp"

namespace cpu_emulator::operations {
    class JumpLess : public Jump {
    public:
        using Jump::Jump;
        void doIt(std::shared_ptr<cpu_emulator::CpuState>) override;
    };
}