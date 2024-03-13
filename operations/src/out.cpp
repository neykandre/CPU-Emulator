#include <iostream>
#include <utility>
#include "../include/out.hpp"

namespace cpu_emulator::operations {
    Out::Out(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr_ = std::move(state_ptr);
    }

    void Out::doIt() {
        std::cout << state_ptr_->stack.top() << std::endl;
        state_ptr_->stack.pop();
    }
}