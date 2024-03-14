#include "../include/preprocessor.hpp"

namespace cpu_emulator {
    std::shared_ptr<operations::baseOperation> Preprocessor::makeOperation(const Instruction& instruction) {
        using namespace operations;
        switch (instruction.type) {
            case commandType::push:
                if (instruction.args[0].type != mapped_arg_type[instruction.type]) {
                    throw ExceptBuilder<invalid_argument>()
                            .setLinePos(instruction.line_pos)
                            .setLineText(instruction.src_string)
                            .setNote("invalid argument")
                            .get();
                }
                return std::shared_ptr<baseOperation>(
                        new Push(std::get<value_type>(instruction.args[0].arg), ptr_state_));

            case commandType::pop:
                return std::shared_ptr<baseOperation>(new Pop(ptr_state_));

            case commandType::pushR:
                if (instruction.args[0].type != mapped_arg_type[instruction.type]) {
                    throw ExceptBuilder<invalid_argument>()
                            .setLinePos(instruction.line_pos)
                            .setLineText(instruction.src_string)
                            .setNote("invalid argument")
                            .get();
                }
                return std::shared_ptr<baseOperation>(
                        new PushR(std::get<enum_registers>(instruction.args[0].arg), ptr_state_));

            case commandType::popR:
                if (instruction.args[0].type != mapped_arg_type[instruction.type]) {
                    throw ExceptBuilder<invalid_argument>()
                            .setLinePos(instruction.line_pos)
                            .setLineText(instruction.src_string)
                            .setNote("invalid argument")
                            .get();
                }
                return std::shared_ptr<baseOperation>(
                        new PopR(std::get<enum_registers>(instruction.args[0].arg), ptr_state_));

            case commandType::add:
                return std::shared_ptr<baseOperation>(new Add(ptr_state_));

            case commandType::sub:
                return std::shared_ptr<baseOperation>(new Sub(ptr_state_));

            case commandType::mul:
                return std::shared_ptr<baseOperation>(new Mul(ptr_state_));

            case commandType::div:
                return std::shared_ptr<baseOperation>(new Div(ptr_state_));

            case commandType::out:
                return std::shared_ptr<baseOperation>(new Out(ptr_state_));

            case commandType::in:
                return std::shared_ptr<baseOperation>(new In(ptr_state_));
//            case commandType::ret:
//                break;
//            case commandType::label:
//                break;

            case commandType::begin:
                begin_was_ = true;
                ptr_state_->head = operations_tape_.size();
                return std::shared_ptr<baseOperation>(new Begin(ptr_state_));

            case commandType::end:
                end_was_ = true;
                end_pos_ = operations_tape_.size();
                return std::shared_ptr<baseOperation>(new End(ptr_state_));

            default:
                return nullptr;
        }
    }

    void Preprocessor::process() {
        Parser parser(file_path_);

        Instruction instruction = parser.getInstruction();
        for (; instruction.type != commandType::eof; instruction = parser.getInstruction()) {
            if (instruction.type == commandType::unknown) {
                throw ExceptBuilder<unknown_command>()
                        .setLinePos(instruction.line_pos)
                        .setLineText(instruction.src_string)
                        .setNote("unknown command")
                        .get();
            }

            if (instruction.args.size() < required_num_of_args[instruction.type]) {
                throw ExceptBuilder<too_few_args>()
                        .setLinePos(instruction.line_pos)
                        .setLineText(instruction.src_string)
                        .setNote("too few arguments")
                        .get();
            }

            if (instruction.args.size() > required_num_of_args[instruction.type]) {
                throw ExceptBuilder<too_many_args>()
                        .setLinePos(instruction.line_pos)
                        .setLineText(instruction.src_string)
                        .setNote("too many arguments")
                        .get();
            }

            std::shared_ptr<operations::baseOperation> new_operation = makeOperation(instruction);
            operations_tape_.push_back(new_operation);
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
        if (end_pos_ <= ptr_state_->head) {
            throw ExceptBuilder<incorrect_order>()
                    .setNote(R"("end" declared before "begin")")
                    .get();
        }
    }

    Preprocessor::Preprocessor(std::shared_ptr<CpuState> state, const std::string& path) {
        ptr_state_ = std::move(state);
        file_path_ = path;
    }

    std::vector<std::shared_ptr<operations::baseOperation>>& Preprocessor::getOperations() {
        return operations_tape_;
    }


}