#include "../include/popStack.hpp"

namespace cpu_emulator::operations {
    void Pop::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr->stack.pop();
    }
}