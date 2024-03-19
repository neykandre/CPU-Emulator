#pragma once

#include <memory>
#include <vector>
#include "../../include/exceptBuilder.hpp"
#include "../../include/settings.hpp"
#include "../../include/state.hpp"
#include "../../include/token.hpp"

namespace cpu_emulator::operations {
    class BaseOperation {
    public:
        BaseOperation() = default;

        virtual void doIt(std::shared_ptr<cpu_emulator::CpuState>) = 0;

        void moveInstruction(Instruction& instruction);

        Instruction& getInstruction();

        size_t getReqArgsNum() const;

        [[nodiscard]] std::strong_ordering isArgsNumValid() const;

        [[nodiscard]] virtual bool isArgTypeValid() const { return true;};

    protected:
        Instruction instruction_;
        size_t required_args_num_{0};
    };
}