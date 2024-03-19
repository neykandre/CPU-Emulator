#include <iostream>
#include "../include/in.hpp"

namespace cpu_emulator::operations {
    void In::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr->stack.push(value_type());
        std::cin >> state_ptr->stack.top();
    }
}