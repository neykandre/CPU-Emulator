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
                            .setNote("\tinvalid argument")
                            .get();
                    std::string except_string = "\n" + std::to_string(instruction.line_pos) + " |\t\t" +
                                                instruction.src_string + "\n" +
                                                "\tinvalid argument";
                    throw invalid_argument(except_string);
                }
                return std::shared_ptr<baseOperation>(
                        new Push(std::get<value_type>(instruction.args[0].arg), ptr_state_));

            case commandType::pop:
                return std::shared_ptr<baseOperation>(new Pop(ptr_state_));

            case commandType::pushR:
                if (instruction.args[0].type != mapped_arg_type[instruction.type]) {
                    std::string except_string = "\n" + std::to_string(instruction.line_pos) + " |\t\t" +
                                                instruction.src_string + "\n" +
                                                "\tinvalid argument";
                    throw invalid_argument(except_string);
                }
                return std::shared_ptr<baseOperation>(
                        new PushR(std::get<enum_registers>(instruction.args[0].arg), ptr_state_));

            case commandType::popR:
                if (instruction.args[0].type != mapped_arg_type[instruction.type]) {
                    std::string except_string = "\n" + std::to_string(instruction.line_pos) + " |\t\t" +
                                                instruction.src_string + "\n" +
                                                "\tinvalid argument";
                    throw invalid_argument(except_string);
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
                std::string except_string = "\n" + std::to_string(instruction.line_pos) + " |\t\t" +
                                            instruction.src_string + "\n" +
                                            "\tunknown command";
                throw unknown_command(except_string);
            }

            if (instruction.args.size() < required_num_of_args[instruction.type]) {
                std::string except_string = "\n" + std::to_string(instruction.line_pos) + " |\t\t" +
                                            instruction.src_string + "\n" +
                                            "\ttoo few arguments (" + std::to_string(instruction.args.size()) + "/" +
                                            std::to_string(required_num_of_args[instruction.type]) + ")";
                throw too_few_args(except_string);
            }

            if (instruction.args.size() > required_num_of_args[instruction.type]) {
                std::string except_string = "\n" + std::to_string(instruction.line_pos) + " |\t\t" +
                                            instruction.src_string + "\n" +
                                            "\ttoo many arguments (" + std::to_string(instruction.args.size()) + "/" +
                                            std::to_string(required_num_of_args[instruction.type]) + ")";
                throw too_many_args(except_string);
            }

            std::shared_ptr<operations::baseOperation> new_operation = makeOperation(instruction);
            operations_tape_.push_back(new_operation);
        }

        if (!begin_was_) {
            throw begin_absence("no \"begin\" command (required)");
        }
        if (!end_was_) {
            throw end_absence("no \"end\" command (required)");
        }
        if (end_pos_ <= ptr_state_->head) {
            throw incorrect_order(R"("end" declared before "begin")");
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