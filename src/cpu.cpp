#include "../include/cpu.hpp"

namespace cpu_emulator {

    void Cpu::setFilePath(const std::string& path) {
        file_path_ = path;
    }

    void Cpu::exec() {
        Preprocessor preprocessor(ptr_state_, file_path_);
        preprocessor.process();
        operations_tape_ = preprocessor.getOperations();

        operations_tape_[ptr_state_->head]->doIt();
        while (ptr_state_->is_running_) {
            ptr_state_->head++;
            operations_tape_[ptr_state_->head]->doIt();
        }
    }
}