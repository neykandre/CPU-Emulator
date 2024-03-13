#include <utility>

#include "../include/sub.hpp"

namespace cpu_emulator::operations {
    Sub::Sub(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr_ = std::move(state_ptr);
    }

    void Sub::doIt() {
        value_type first = state_ptr_->stack.top();
        state_ptr_->stack.pop();
        value_type second = state_ptr_->stack.top();
        state_ptr_->stack.pop();
        state_ptr_->stack.push(first - second);
    }
}