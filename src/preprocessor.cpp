#include "../include/preprocessor.hpp"


namespace cpu_emulator {

    too_many_args::too_many_args(const std::string& message)
            : std::logic_error(message),
              message(message) {}

    too_few_args::too_few_args(const std::string& message)
            : std::logic_error(message),
              message(message) {}

    unknown_command::unknown_command(const std::string& message)
            : std::logic_error(message),
              message(message) {}

    invalid_argument::invalid_argument(const std::string& message)
            : std::invalid_argument(message),
              message(message) {}

    std::shared_ptr<operations::baseOperation> Preprocessor::makeOperation(const Instruction& instruction) {
        using namespace operations;
        switch (instruction.type) {
            case commandType::push:
                if (instruction.args[0].type != mapped_arg_type[instruction.type]) {
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
                ptr_state_->head = operations_tape_.size();
                return std::shared_ptr<baseOperation>(new Begin(ptr_state_));
            case commandType::end:
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
    }

    Preprocessor::Preprocessor(std::shared_ptr<CpuState> state, const std::string& path) {
        ptr_state_ = std::move(state);
        file_path_ = path;
    }

    std::vector<std::shared_ptr<operations::baseOperation>>& Preprocessor::getOperations() {
        return operations_tape_;
    }


}