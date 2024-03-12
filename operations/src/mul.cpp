#include "../include/mul.hpp"

namespace cpu_emulator::operations {
    Mul::Mul(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr_ = state_ptr;
    }

    void Mul::doIt() {
        value_type first = state_ptr_->stack.top();
        state_ptr_->stack.pop();
        value_type second = state_ptr_->stack.top();
        state_ptr_->stack.pop();
        state_ptr_->stack.push(first * second);
    }
}