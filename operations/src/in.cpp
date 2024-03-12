#include <iostream>
#include "../include/in.hpp"

namespace cpu_emulator::operations {
    In::In(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr_ = state_ptr;
    }

    void In::doIt() {
        state_ptr_->stack.push(value_type());
        std::cin >> state_ptr_->stack.top();
    }
}