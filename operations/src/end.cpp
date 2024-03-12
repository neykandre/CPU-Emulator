#include "../include/end.hpp"

namespace cpu_emulator::operations {
    End::End(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr_ = state_ptr;
    }

    void End::doIt() {
    }
}