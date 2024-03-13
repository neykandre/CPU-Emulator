<<<<<<< HEAD
=======
#include <utility>

>>>>>>> 4251488 (base commands (fibonacci))
#include "../include/add.hpp"

namespace cpu_emulator::operations {
    Add::Add(std::shared_ptr<cpu_emulator::CpuState> state_ptr) {
<<<<<<< HEAD
        state_ptr_ = state_ptr;
=======
        state_ptr_ = std::move(state_ptr);
>>>>>>> 4251488 (base commands (fibonacci))
    }

    void Add::doIt() {
        value_type first = state_ptr_->stack.top();
        state_ptr_->stack.pop();
        value_type second = state_ptr_->stack.top();
        state_ptr_->stack.pop();
        state_ptr_->stack.push(first + second);
    }
}