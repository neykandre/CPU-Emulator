#pragma once

#include <memory>
#include "baseOperation.hpp"
#include "../../include/settings.hpp"
#include "../../include/state.hpp"

namespace cpu_emulator::operations {
    class Pop : public baseOperation {
    public:
        explicit Pop(std::shared_ptr<cpu_emulator::CpuState>);

        void doIt() override;
    };
}