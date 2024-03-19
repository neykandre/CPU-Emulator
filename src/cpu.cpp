#include <iostream>
#include "../include/cpu.hpp"

namespace cpu_emulator {

    void Cpu::setFilePath(const std::string& path) {
        file_path_ = path;
    }

    void Cpu::exec() {
        Preprocessor preprocessor(file_path_);
        try {
            preprocessor.process();
            successful_preprocessed_ = true;
        }
        catch (const preprocess_error& e) {
            std::cerr << "PREPROCESS ERROR" << std::endl;
            std::cerr << e.what() << std::endl;
        }

        if (successful_preprocessed_) {
            operations_tape_ = preprocessor.getOperations();
            ptr_state_->head = preprocessor.getStartPos();

            operations_tape_[ptr_state_->head]->doIt(ptr_state_);
            while (ptr_state_->is_running) {
                ptr_state_->head++;
                operations_tape_[ptr_state_->head]->doIt(ptr_state_);
            }
        }
    }
}