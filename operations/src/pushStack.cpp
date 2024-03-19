#include "../include/pushStack.hpp"

namespace cpu_emulator::operations {
    Push::Push()
            : BaseOperation() {
        required_args_num_ = 1;
    }

    void Push::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        auto value = std::get<value_type>(instruction_.args[0].arg);
        state_ptr->stack.push(value);
    }

    bool Push::isArgTypeValid() const {
        return instruction_.args[0].type == argType::value;
    }
}