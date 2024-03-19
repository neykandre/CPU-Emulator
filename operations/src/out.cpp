#include <iostream>
#include "../include/out.hpp"

namespace cpu_emulator::operations {
    void Out::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        std::cout << state_ptr->stack.top() << std::endl;
        state_ptr->stack.pop();
    }
}