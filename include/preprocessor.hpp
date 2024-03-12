#pragma once

#include <string>
#include <vector>
#include <map>
#include "../operations/include/operations.hpp"
#include "parser.hpp"
#include "settings.hpp"
#include "state.hpp"
#include "token.hpp"

namespace cpu_emulator {

    class Preprocessor {
    private:
        std::string file_path_;

        bool file_was_opened_{false};

        void setFromFile();

//        std::map<std::string, size_t> labels_map_;
    public:


        CpuState& getStartState();

        std::vector<operations::baseOperation*>& getOperationsTape();
    };
}