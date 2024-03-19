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
        using base_op_ptr = std::shared_ptr<operations::BaseOperation>;
        using vec_op = std::vector<base_op_ptr>;
    private:
        std::string file_path_;
        vec_op operations_tape_;
        bool begin_was_{false};
        bool end_was_{false};
        size_t start_pos_{0};
        size_t end_pos_{0};

        template<class T>
        static constexpr auto make_op_ptr = []() { return std::make_shared<T>(T()); };

        static std::map<commandType, std::function<base_op_ptr()>> make_operation;

        std::map<std::string, size_t> mapped_labels;

        std::multimap<std::string, base_op_ptr> jumps;
    public:
        Preprocessor() = delete;

        Preprocessor(const std::string&); //NOLINT

        void process();

        vec_op& getOperations();

        static base_op_ptr makeOperation(commandType);

        size_t getStartPos() const;
    };
}