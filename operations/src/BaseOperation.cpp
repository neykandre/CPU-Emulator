#include "../include/BaseOperation.hpp"

namespace cpu_emulator::operations {
    void BaseOperation::moveInstruction(Instruction& instruction) {
        instruction_ = std::move(instruction);
    }

    Instruction& BaseOperation::getInstruction() {
        return instruction_;
    }

    size_t BaseOperation::getReqArgsNum() const {
        return required_args_num_;
    }

    std::strong_ordering BaseOperation::isArgsNumValid() const {
        return instruction_.args.size() <=> required_args_num_;
    }
}