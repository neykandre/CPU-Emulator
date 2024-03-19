#include "../include/call.hpp"

namespace cpu_emulator::operations {
    void Call::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr->call_stack.push({state_ptr->stack.size(), state_ptr->head});
        Jump::doIt(state_ptr);
    }
}