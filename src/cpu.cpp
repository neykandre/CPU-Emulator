#include <iostream>
#include "../include/cpu.hpp"
#include <binSerializer.hpp>

namespace cpu_emulator {
    void Cpu::exec(const std::string& file_path) {
        successful_preprocessed_ = false;
        Preprocessor preprocessor(file_path);
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

    void Cpu::execBinary(const std::string& bin_path) {
        try {
            Serializer serializer;
            auto head_vec = serializer.deserialize(bin_path);
            ptr_state_->head = head_vec.first;
            operations_tape_ = head_vec.second;
        }
        catch (const no_file& e) {
            std::cerr << "\nDESERIALIZE ERROR" << std::endl;
            std::cerr << e.what() << std::endl;
        }

        operations_tape_[ptr_state_->head]->doIt(ptr_state_);
        while (ptr_state_->is_running) {
            ptr_state_->head++;
            operations_tape_[ptr_state_->head]->doIt(ptr_state_);
        }
    }
}