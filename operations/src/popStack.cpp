#include "../include/popStack.hpp"

namespace cpu_emulator::operations {
    Pop::Pop(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr_ = state_ptr;
    }

    void Pop::doIt() {
        state_ptr_->stack.pop();
    }
}