#include "../include/popRegister.hpp"

namespace cpu_emulator::operations {
    PopR::PopR()
            : BaseOperation() {
        required_args_num_ = 1;
    }

    void PopR::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        auto reg = std::get<enum_registers>(instruction_.args[0].arg);
        state_ptr->registers[static_cast<size_t>(reg)] = state_ptr->stack.top();
        state_ptr->stack.pop();
    }

    bool PopR::isArgTypeValid() const {
        return instruction_.args[0].type == argType::reg;
    }
}