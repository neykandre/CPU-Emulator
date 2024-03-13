#pragma once

#include <memory>
#include "baseOperation.hpp"
#include "../../include/settings.hpp"
#include "../../include/state.hpp"

namespace cpu_emulator::operations {
    class In : public baseOperation {
    public:
        explicit In(std::shared_ptr<cpu_emulator::CpuState>);

        void doIt() override;
    };
}