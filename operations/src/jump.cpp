#include "../include/jump.hpp"

namespace cpu_emulator::operations {
    Jump::Jump()
            : BaseOperation() {
        required_args_num_ = 1;
    }

    void Jump::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        size_t op_idx = std::visit([](auto&& arg) {return static_cast<size_t>(arg);}, instruction_.args[0].arg);
        state_ptr->head = op_idx;
    }

    bool Jump::isArgTypeValid() const {
        return instruction_.args[0].type == argType::label_idx;
    }
}