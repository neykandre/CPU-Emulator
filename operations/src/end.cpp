#include "../include/end.hpp"

namespace cpu_emulator::operations {
    void End::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr->is_running = false;
    }
}