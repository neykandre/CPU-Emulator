#include "../include/begin.hpp"

namespace cpu_emulator::operations {
    void Begin::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr->is_running = true;
    }
}