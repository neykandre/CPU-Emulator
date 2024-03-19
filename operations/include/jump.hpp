#pragma once

#include "BaseOperation.hpp"

namespace cpu_emulator::operations {
    class Jump : public BaseOperation {
    public:
        explicit Jump();

        virtual void doIt(std::shared_ptr<cpu_emulator::CpuState>) override;

        bool isArgTypeValid() const override;
    };
}