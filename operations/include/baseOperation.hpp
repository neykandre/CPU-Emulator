#pragma once

#include <map>
#include <memory>
#include "../../include/settings.hpp"
#include "../../include/state.hpp"

namespace cpu_emulator::operations {
    class baseOperation {
    public:
        baseOperation() = default;
        virtual void doIt() = 0;

    protected:
        std::shared_ptr<cpu_emulator::CpuState> state_ptr_;
        std::map<enum_registers, register_type*> mapped_regs = {
                {enum_registers::eax, &state_ptr_->registers.EAX},
                {enum_registers::ebx, &state_ptr_->registers.EBX},
                {enum_registers::ecx, &state_ptr_->registers.ECX},
                {enum_registers::edx, &state_ptr_->registers.EDX},
        };
    };
}