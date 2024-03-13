#include <utility>

#include "../include/begin.hpp"

namespace cpu_emulator::operations {
    Begin::Begin(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr_ = std::move(state_ptr);
    }

    void Begin::doIt() {
        state_ptr_->is_running_ = true;
    }
}