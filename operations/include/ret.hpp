#pragma once

#include "BaseOperation.hpp"

namespace cpu_emulator::operations {
    class Ret : public BaseOperation {
        using BaseOperation::BaseOperation;

        void doIt(std::shared_ptr<cpu_emulator::CpuState>) override;
    };
}