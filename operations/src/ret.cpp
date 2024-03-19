#include "../include/ret.hpp"

namespace cpu_emulator::operations {
    void Ret::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        size_t sp = state_ptr->call_stack.top().first;
        size_t pr_head = state_ptr->call_stack.top().second;
        state_ptr->head = pr_head;
        state_ptr->call_stack.pop();
        while (state_ptr->stack.size() > sp) {
            state_ptr->stack.pop();
        }
    }
}