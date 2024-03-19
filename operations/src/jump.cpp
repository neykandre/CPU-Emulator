#include "../include/jump.hpp"

namespace cpu_emulator::operations {
    Jump::Jump()
            : BaseOperation() {
        required_args_num_ = 1;
    }

    void Jump::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        state_ptr->head = std::get<size_t>(instruction_.args[0].arg);
    }

    bool Jump::isArgTypeValid() const {
        return instruction_.args[0].type == argType::label_idx;
    }
}