#include <utility>

#include "../include/pushRegister.hpp"

namespace cpu_emulator::operations {
    PushR::PushR(enum_registers enum_reg, std::shared_ptr<cpu_emulator::CpuState> state_ptr)
            : reg(enum_reg) {
        state_ptr_ = std::move(state_ptr);
    }

    void PushR::doIt() {
        state_ptr_->stack.push(state_ptr_->registers[static_cast<size_t>(reg)]);
    }
}