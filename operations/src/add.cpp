#include "../include/add.hpp"

namespace cpu_emulator::operations {
    void Add::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        value_type first = state_ptr->stack.top();
        state_ptr->stack.pop();
        value_type second = state_ptr->stack.top();
        state_ptr->stack.pop();
        state_ptr->stack.push(first + second);
    }
}