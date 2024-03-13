#pragma once

#include <memory>
#include "baseOperation.hpp"
#include "../../include/settings.hpp"
#include "../../include/state.hpp"

namespace cpu_emulator::operations {
    class Push : public baseOperation {
    public:
        explicit Push(value_type, std::shared_ptr<cpu_emulator::CpuState>);

        void doIt() override;

    private:
        value_type value_;
    };
}