#pragma once

#include "settings.hpp"
#include "stack.hpp"

namespace cpu_emulator {
    enum class enum_registers {
        eax,
        ebx,
        ecx,
        edx
    };

    struct Registers {
        register_type EAX;
        register_type EBX;
        register_type ECX;
        register_type EDX;
    };

    struct CpuState {
        Registers registers;

        size_t head;

        stack_lib::Stack<value_type> stack;
    };
}