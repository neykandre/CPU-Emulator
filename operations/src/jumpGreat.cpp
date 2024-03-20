#include "../include/jumpGreat.hpp"

namespace cpu_emulator::operations {
    void JumpGreat::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        value_type a = state_ptr->stack.top();
        state_ptr->stack.pop();
        value_type b = state_ptr->stack.top();
        state_ptr->stack.push(a);
        if (a > b) {
            Jump::doIt(state_ptr);
        }
    }
}