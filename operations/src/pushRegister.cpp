#include "../include/pushRegister.hpp"

namespace cpu_emulator::operations {
    PushR::PushR()
            : BaseOperation() {
        required_args_num_ = 1;
        instruction_.args.push_back({.arg = enum_registers()});
    }

    void PushR::doIt(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
        size_t reg_idx = std::visit([](auto&& arg) { return static_cast<size_t>(arg); },
                                    instruction_.args[0].arg);
        state_ptr->stack.push(state_ptr->registers[reg_idx]);
    }

    bool PushR::isArgTypeValid() const {
        return instruction_.args[0].type == argType::reg;
    }
}