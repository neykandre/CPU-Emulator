#pragma once

#include <memory>
#include "BaseOperation.hpp"
#include "../../include/settings.hpp"
#include "../../include/state.hpp"

namespace cpu_emulator::operations {
    class PushR : public BaseOperation {
    public:
        explicit PushR();

        void doIt(std::shared_ptr<cpu_emulator::CpuState>) override;

        bool isArgTypeValid() const override;
    };
}