#include <map>
#include "../include/pushRegister.hpp"

namespace cpu_emulator::operations {
    PushR::PushR(enum_registers enum_reg, std::shared_ptr<cpu_emulator::CpuState> state_ptr)
            : reg(enum_reg) {
        state_ptr_ = state_ptr;
    }

    void PushR::doIt() {
        state_ptr_->stack.push(*mapped_regs[reg]);
    }
}