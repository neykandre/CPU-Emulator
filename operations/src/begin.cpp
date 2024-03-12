#include "../include/begin.hpp"

namespace cpu_emulator::operations {
    Begin::Begin(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr_ = state_ptr;
    }

    void Begin::doIt() {
    }
}