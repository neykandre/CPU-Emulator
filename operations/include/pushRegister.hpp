#pragma once

#include <memory>
#include "baseOperation.hpp"
#include "../../include/settings.hpp"
#include "../../include/state.hpp"

namespace cpu_emulator::operations {
    class PushR : public baseOperation {
    public:
        explicit PushR(enum_registers, std::shared_ptr<cpu_emulator::CpuState>);

        void doIt() override;

    private:
        enum_registers reg;
    };
}