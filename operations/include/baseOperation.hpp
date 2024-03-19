#pragma once

#include <map>
#include <memory>
#include "../../include/settings.hpp"
#include "../../include/state.hpp"

namespace cpu_emulator::operations {
    class baseOperation {
    public:
        baseOperation() = default;
        virtual void doIt() = 0;

    protected:
        std::shared_ptr<cpu_emulator::CpuState> state_ptr_;
    };
}