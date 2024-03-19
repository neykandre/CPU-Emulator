#pragma once

#include <array>
#include "settings.hpp"
#include "stack.hpp"

namespace cpu_emulator {
    enum class enum_registers {
        eax,
        ebx,
        ecx,
        edx,
        _count
    };

    struct CpuState {
        std::array<register_type, static_cast<size_t>(enum_registers::_count)> registers;

        size_t head;

        stack_lib::Stack<value_type> stack;

        bool is_running;
    };
}