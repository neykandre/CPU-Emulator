#pragma once

#include <memory>
#include "BaseOperation.hpp"
#include "../../include/settings.hpp"
#include "../../include/state.hpp"

namespace cpu_emulator::operations {
    class Pop : public BaseOperation {
    public:
        using BaseOperation::BaseOperation;

        void doIt(std::shared_ptr<cpu_emulator::CpuState>) override;
    };
}