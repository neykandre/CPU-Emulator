#pragma once

#include <string>
#include <vector>
#include <map>
#include "../operations/include/operations.hpp"
#include "parser.hpp"
#include "settings.hpp"
#include "state.hpp"
#include "token.hpp"
#include "exceptBuilder.hpp"

namespace cpu_emulator {
    class Preprocessor {
    private:
        std::string file_path_;
        std::vector<std::shared_ptr<operations::baseOperation>> operations_tape_;
        std::shared_ptr<CpuState> ptr_state_;
        bool begin_was_{false};
        bool end_was_{false};
        size_t end_pos_{0};

        std::map<commandType, size_t> required_num_of_args{
                {commandType::push,  1},
                {commandType::pushR, 1},
                {commandType::popR,  1}
        };

        std::map<commandType, argType> mapped_arg_type{
                {commandType::push,  argType::value},
                {commandType::pushR, argType::reg},
                {commandType::popR,  argType::reg}
        };

        std::shared_ptr<operations::baseOperation> makeOperation(const Instruction&);

//        std::map<std::string, size_t> labels_map_;
    public:
        Preprocessor() = delete;

        Preprocessor(std::shared_ptr<CpuState>, const std::string&); //NOLINT

        void process();

        std::vector<std::shared_ptr<operations::baseOperation>>& getOperations();

//        std::map<std::string, size_t> getLabels();
    };
}