#include "../include/popRegister.hpp"

namespace cpu_emulator::operations {
    PopR::PopR(enum_registers enum_reg, std::shared_ptr<cpu_emulator::CpuState> state_ptr)
            : reg(enum_reg) {
        state_ptr_ = state_ptr;
    }

    void PopR::doIt() {
        *mapped_regs[reg] = state_ptr_->stack.top();
        state_ptr_->stack.pop();
    }
}