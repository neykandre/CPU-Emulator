#pragma once

#include "operations.hpp"

namespace cpu_emulator::operations {
    template<class T>
    class operationBuilder {
    public:
        T* build();
    private:

    };
}