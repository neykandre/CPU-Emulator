#pragma once

#include <string>
#include "../operations/include/operations.hpp"
#include "preprocessor.hpp"
#include "settings.hpp"
#include "state.hpp"

namespace cpu_emulator {
    class Cpu {
    private:
        std::shared_ptr<CpuState> ptr_state_{std::make_shared<CpuState>()};
        std::string file_path_;
        bool successful_preprocessed_{false};

        std::vector<std::shared_ptr<operations::BaseOperation>> operations_tape_;

    public:

        void setFilePath(const std::string&);

        void exec();
    };
}