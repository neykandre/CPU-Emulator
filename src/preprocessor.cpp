#include "parser.hpp"
#include "state.hpp"
#include "exceptBuilder.hpp"
#include "../include/preprocessor.hpp"

namespace cpu_emulator {
    std::map<commandType, std::function<Preprocessor::base_op_ptr()>> Preprocessor::make_operation = {
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
            {commandType::jumpEq,    make_op_ptr<operations::JumpEq>},
            {commandType::jumpNe,    make_op_ptr<operations::JumpNe>},
            {commandType::jumpGr,    make_op_ptr<operations::JumpGreat>},
            {commandType::jumpGrEq,  make_op_ptr<operations::JumpGreatEq>},
            {commandType::jumpLes,   make_op_ptr<operations::JumpLess>},
            {commandType::jumpLesEq, make_op_ptr<operations::JumpLessEq>},
            {commandType::call,      make_op_ptr<operations::Call>},
            {commandType::ret,       make_op_ptr<operations::Ret>}
    };

    Preprocessor::Preprocessor(const std::string& path)
            : file_path_(path) {}

    void Preprocessor::process() {
        Parser parser(file_path_);

        Instruction instruction = parser.getInstruction();
        for (; instruction.type != commandType::eof; instruction = parser.getInstruction()) {
            if (instruction.type == commandType::label) {
                if (instruction.args.size() != 1 || instruction.args[0].type != argType::label) {
                    throw ExceptBuilder<preprocess_error>()
                            .setLinePos(instruction.line_pos)
                            .setLineText(instruction.src_string)
                            .setNote("Failed while parsing. Invalid label definition.\n")
                            .get();
                }
                mapped_labels[instruction.args[0].label] = operations_tape_.size();
            } else {
                base_op_ptr new_operation = make_operation[instruction.type]();

                if (!new_operation) {
                    throw ExceptBuilder<unknown_command>()
                            .setLinePos(instruction.line_pos)
                            .setLineText(instruction.src_string)
                            .setNote("unknown command\n")
                            .get();
                }

                new_operation->moveInstruction(instruction);

                if (new_operation->isArgsNumValid() == std::strong_ordering::greater) {
                    throw ExceptBuilder<too_many_args>()
                            .setLinePos(new_operation->getInstruction().line_pos)
                            .setLineText(new_operation->getInstruction().src_string)
                            .setNote("too many arguments\n")
                            .get();
                }

                if (new_operation->isArgsNumValid() == std::strong_ordering::less) {
                    throw ExceptBuilder<too_few_args>()
                            .setLinePos(new_operation->getInstruction().line_pos)
                            .setLineText(new_operation->getInstruction().src_string)
                            .setNote("too few arguments\n")
                            .get();
                }

                operations_tape_.push_back(new_operation);

                if (instruction.type == commandType::begin) {
                    start_pos_ = operations_tape_.size() - 1;
                    begin_was_ = true;
                } else if (instruction.type == commandType::end) {
                    end_pos_ = operations_tape_.size() - 1;
                    end_was_ = true;
                } else if (instruction.type >= commandType::jump &&
                           instruction.type <= commandType::call) {
                    std::string s = new_operation->getInstruction().args[0].label;
                    jumps.insert(std::make_pair(s, new_operation));
                }
            }
        }

        for (auto& rec: jumps) {
            if (!mapped_labels.contains(rec.first)) {
                throw ExceptBuilder<invalid_label>()
                        .setLinePos(rec.second->getInstruction().line_pos)
                        .setLineText(rec.second->getInstruction().src_string)
                        .setNote("No such label to jump: " + rec.first + "\n")
                        .get();
            }
            rec.second->getInstruction().args[0].type = argType::label_idx;
            rec.second->getInstruction().args[0].arg = mapped_labels[rec.first] - 1;
        }

        for (const auto& operation: operations_tape_) {
            if (!operation->isArgTypeValid()) {
                throw ExceptBuilder<invalid_argument_type>()
                        .setLinePos(operation->getInstruction().line_pos)
                        .setLineText(operation->getInstruction().src_string)
                        .setNote("invalid argument type")
                        .get();
            }
        }

        if (!begin_was_) {
            throw ExceptBuilder<begin_absence>()
                    .setNote("no \"begin\" command (required)")
                    .get();
        }
        if (!end_was_) {
            throw ExceptBuilder<end_absence>()
                    .setNote("no \"end\" command (required)")
                    .get();
        }
        if (end_pos_ <= start_pos_) {
            throw ExceptBuilder<incorrect_order>()
                    .setNote(R"("end" declared before "begin")")
                    .get();
        }
    }

    Preprocessor::vec_op& Preprocessor::getOperations() {
        return operations_tape_;
    }

    size_t Preprocessor::getStartPos() const {
        return start_pos_;
    }

    Preprocessor::base_op_ptr Preprocessor::makeOperation(commandType type) {
        return make_operation[type]();
    }


}