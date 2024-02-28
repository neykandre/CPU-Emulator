#pragma once

#include <cstdint>

namespace cpu {
    class Cpu {
        using register_type = uint16_t;

        struct Register {
            register_type EAX;
            register_type EBX;
            register_type ECX;
            register_type EDX;
        };



    };
}