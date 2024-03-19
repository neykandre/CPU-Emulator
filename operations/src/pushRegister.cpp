#include "../include/pushRegister.hpp"

namespace cpu_emulator::operations {
    PushR::PushR()
            : BaseOperation() {
        required_args_num_ = 1;
    }

    void PushR::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        auto reg = std::get<enum_registers>(instruction_.args[0].arg);
        state_ptr->stack.push(state_ptr->registers[static_cast<size_t>(reg)]);
    }

    bool PushR::isArgTypeValid() const {
        return instruction_.args[0].type == argType::reg;
    }
}