#include "../include/baseOperation.hpp"

namespace cpu_emulator::operations {
    baseOperation::baseOperation(const cpu_emulator::Instruction& instruction,
                                 std::shared_ptr<cpu_emulator::CpuState> state)
            : instruction_(instruction),
              state_ptr_(state) {}
}