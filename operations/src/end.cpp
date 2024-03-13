#include <utility>

#include "../include/end.hpp"

namespace cpu_emulator::operations {
    End::End(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr_ = std::move(state_ptr);
    }

    void End::doIt() {
        state_ptr_->is_running_ = false;
    }
}