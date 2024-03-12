#include "../include/pushStack.hpp"

namespace cpu_emulator::operations {
    Push::Push(value_type value, std::shared_ptr<cpu_emulator::CpuState> state_ptr)
            : value_(value) {
        state_ptr_ = state_ptr;
    }

    void Push::doIt() {
        state_ptr_->stack.push(value_);
    }
}