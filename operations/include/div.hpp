#pragma once

#include <memory>
#include "baseOperation.hpp"
#include "../../include/settings.hpp"
#include "../../include/state.hpp"

namespace cpu_emulator::operations {
    class Div : public baseOperation {
    public:
        explicit Div(std::shared_ptr<cpu_emulator::CpuState>);

        void doIt() override;
    };
}