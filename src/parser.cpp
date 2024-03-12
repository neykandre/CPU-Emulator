//#include <format>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include "../include/parser.hpp"

namespace cpu_emulator {

    too_few_args::too_few_args(size_t line_pos, int args_num, std::string& command_name) :
            std::logic_error(""){

    }

    unknown_command::unknown_command(const std::string& message)
            : std::logic_error(message),
              message(message) {}

    std::map<std::string, commandType> mapped_command_type{
            {"push",  commandType::push},
            {"pop",   commandType::pop},
            {"pushr", commandType::pushR},
            {"popr",  commandType::popR},
            {"add",   commandType::add},
            {"sub",   commandType::sub},
            {"mul",   commandType::mul},
            {"div",   commandType::div},
            {"out",   commandType::out},
            {"in",    commandType::in},
            {"ret",   commandType::ret},
            {"begin", commandType::begin},
            {"end",   commandType::end}
    };

    ParsedLine Parser::parseLine(const std::string& line, size_t line_pos) {
        std::regex pattern(R"(\w+)");
        std::sregex_iterator start_iter(line.begin(), line.end(), pattern);
        std::sregex_iterator end_iter;
        commandType type = mapped_command_type[start_iter->str()];

        if (type == commandType::unknown) {
            if (std::regex_match(start_iter->str(), std::regex(R"(\w+:)"))) {
                type = commandType::label;
            } else {
//                throw unknown_command(std::format("Unknown command in line {}", std::to_string(line_pos)));
                std::string error_string = "Unknown command in line " + std::to_string(line_pos);
                throw unknown_command(error_string);
            }
        }

        if (type != commandType::label) {
            start_iter++;
        }

        std::vector<std::string> args;
        for (auto i = start_iter; i != end_iter; ++i) {
            args.push_back(i->str());
        }

        ParsedLine retLine;
        retLine.type = type;
        retLine.args = std::move(args);
        return retLine;
    }

    void Parser::setFilePath(const std::string& path) {
        file_path_ = path;
        was_opened_ = false;
    }

    void Parser::setFilePath(std::string&& path) {
        file_path_ = std::move(path);
        was_opened_ = false;
    }

    std::vector<std::unique_ptr<operations::baseOperation>>& Parser::getOperations() {
        if (!was_opened_) {
            parseFile();
        }
        return operations_tape_;
    }

    void Parser::parseFile() {
        std::ifstream in(file_path_);

        size_t line_pos = 0;
        for (std::string line; std::getline(in, line); ++line_pos) {
            ParsedLine parsed_line = parseLine(line, line_pos);
            switch (parsed_line.type) {
                case commandType::push:
                    if (parsed_line.args.size() < 1) {
                        throw too_few_args("Line " + std::to_string(line_pos) + ": \ntoo few arguments\n"\
                        "push: " + std::to_string(parsed_line.args.size()) + " of 1")
                    }
                    break;
                case commandType::pop:
                    break;
                case commandType::pushR:
                    break;
                case commandType::popR:
                    break;
                case commandType::add:
                    break;
                case commandType::sub:
                    break;
                case commandType::mul:
                    break;
                case commandType::div:
                    break;
                case commandType::out:
                    break;
                case commandType::in:
                    break;
                case commandType::ret:
                    break;
                case commandType::label:
                    break;
                case commandType::begin:
                    break;
                case commandType::end:
                    break;
                case commandType::unknown:
                    break;
            }
        }

        was_opened_ = true;
    }
}