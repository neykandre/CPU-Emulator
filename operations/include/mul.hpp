#pragma once

#include <memory>
#include "baseOperation.hpp"
#include "../../include/settings.hpp"
#include "../../include/state.hpp"

namespace cpu_emulator::operations {
    class Mul : public baseOperation {
    public:
        explicit Mul(std::shared_ptr<cpu_emulator::CpuState>);

        void doIt() override;
    };
}