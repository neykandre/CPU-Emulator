#include "../include/preprocessor.hpp"

namespace cpu_emulator {
    Preprocessor::Preprocessor(const std::string& path)
            : file_path_(path) {}

    void Preprocessor::process() {
        Parser parser(file_path_);

        Instruction instruction = parser.getInstruction();
        for (; instruction.type != commandType::eof; instruction = parser.getInstruction()) {
            if (instruction.type == commandType::label) {
                //TODO exceptions
                mapped_labels[std::get<std::string>(instruction.args[0].arg)] = operations_tape_.size();
            } else {
                std::shared_ptr<operations::BaseOperation> new_operation = make_operation[instruction.type]();

                if (!new_operation) {
                    throw ExceptBuilder<unknown_command>()
                            .setLinePos(instruction.line_pos)
                            .setLineText(instruction.src_string)
                            .setNote("unknown command")
                            .get();
                }

                new_operation->moveInstruction(instruction);

                if (new_operation->isArgsNumValid() == std::strong_ordering::greater) {
                    throw ExceptBuilder<too_many_args>()
                            .setLinePos(new_operation->getInstruction().line_pos)
                            .setLineText(new_operation->getInstruction().src_string)
                            .setNote("too many arguments")
                            .get();
                }

                if (new_operation->isArgsNumValid() == std::strong_ordering::less) {
                    throw ExceptBuilder<too_few_args>()
                            .setLinePos(new_operation->getInstruction().line_pos)
                            .setLineText(new_operation->getInstruction().src_string)
                            .setNote("too few arguments")
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
                           instruction.type <= commandType::jumpLesEq) {
                    std::string s = std::get<std::string>(new_operation->getInstruction().args[0].arg);
                    jumps.insert(std::make_pair(s, new_operation));
                }
            }
        }

        for (auto& rec: jumps) {
            if (!mapped_labels.contains(rec.first)) {
                throw ExceptBuilder<invalid_label>()
                        .setLinePos(rec.second->getInstruction().line_pos)
                        .setLineText(rec.second->getInstruction().src_string)
                        .setNote("No such label to jump: " + rec.first)
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

    std::vector<std::shared_ptr<operations::BaseOperation>>& Preprocessor::getOperations() {
        return operations_tape_;
    }

    size_t Preprocessor::getStartPos() const {
        return start_pos_;
    }


}