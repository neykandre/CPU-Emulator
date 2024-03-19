#pragma once

#include <string>
#include <vector>
#include <map>
#include "parser.hpp"
#include "settings.hpp"
#include "state.hpp"
#include "token.hpp"
#include "exceptBuilder.hpp"
#include "../operations/include/operations.hpp"

namespace cpu_emulator {
    class Preprocessor {
    private:
        std::string file_path_;
        std::vector<std::shared_ptr<operations::BaseOperation>> operations_tape_;
        bool begin_was_{false};
        bool end_was_{false};
        size_t start_pos_{0};
        size_t end_pos_{0};

        template<class T>
        static constexpr auto make_op_ptr = []() { return std::make_shared<T>(T()); };

        std::map<commandType, std::function<std::shared_ptr<operations::BaseOperation>()>> make_operation{
                {commandType::unknown,   []() { return nullptr; }},
                {commandType::push,      make_op_ptr<operations::Push>},
                {commandType::pop,       make_op_ptr<operations::Pop>},
                {commandType::pushR,     make_op_ptr<operations::PushR>},
                {commandType::popR,      make_op_ptr<operations::PopR>},
                {commandType::add,       make_op_ptr<operations::Add>},
                {commandType::sub,       make_op_ptr<operations::Sub>},
                {commandType::mul,       make_op_ptr<operations::Mul>},
                {commandType::div,       make_op_ptr<operations::Div>},
                {commandType::out,       make_op_ptr<operations::Out>},
                {commandType::in,        make_op_ptr<operations::In>},
                {commandType::begin,     make_op_ptr<operations::Begin>},
                {commandType::end,       make_op_ptr<operations::End>},
                {commandType::jump,      make_op_ptr<operations::Jump>},
                {commandType::jumpEq,      make_op_ptr<operations::JumpEq>},
                {commandType::jumpNe,    make_op_ptr<operations::JumpNe>},
                {commandType::jumpGr,    make_op_ptr<operations::JumpGreat>},
                {commandType::jumpGrEq,  make_op_ptr<operations::JumpGreatEq>},
                {commandType::jumpLes,   make_op_ptr<operations::JumpLess>},
                {commandType::jumpLesEq, make_op_ptr<operations::JumpLessEq>}
        };

        std::map<std::string, size_t> mapped_labels;

        std::multimap<std::string, std::shared_ptr<operations::BaseOperation>> jumps;
    public:
        Preprocessor() = delete;

        Preprocessor(const std::string&); //NOLINT

        void process();

        std::vector<std::shared_ptr<operations::BaseOperation>>& getOperations();

        size_t getStartPos() const;
    };
}