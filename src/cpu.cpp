#include <iostream>
#include "../include/cpu.hpp"

namespace cpu_emulator {

    void Cpu::setFilePath(const std::string& path) {
        file_path_ = path;
    }

    void Cpu::exec() {
        Preprocessor preprocessor(ptr_state_, file_path_);
        try {
            preprocessor.process();
            preprocessed_ = true;
        }
        catch (const preprocess_error& e) {
            std::cerr << e.what() << std::endl;
        }

        if (preprocessed_) {
            operations_tape_ = preprocessor.getOperations();

            operations_tape_[ptr_state_->head]->doIt();
            while (ptr_state_->is_running_) {
                ptr_state_->head++;
                operations_tape_[ptr_state_->head]->doIt();
            }
        }
    }
}