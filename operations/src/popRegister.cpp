#include <utility>

#include "../include/popRegister.hpp"

namespace cpu_emulator::operations {
    PopR::PopR(enum_registers enum_reg, std::shared_ptr<cpu_emulator::CpuState> state_ptr)
            : reg(enum_reg) {
        state_ptr_ = std::move(state_ptr);
    }

    void PopR::doIt() {
        state_ptr_->registers[static_cast<size_t>(reg)] = state_ptr_->stack.top();
        state_ptr_->stack.pop();
    }
}