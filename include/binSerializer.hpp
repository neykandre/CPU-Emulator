#pragma once

#include <string>
#include <vector>
#include <memory>
#include <regex>
#include "../operations/include/operations.hpp"

namespace cpu_emulator {
    class Serializer {
        using base_op_ptr = std::shared_ptr<operations::BaseOperation>;
        using vec_op = std::vector<base_op_ptr>;
    public:
        void serialize(const std::string&);

        std::pair<size_t, vec_op> deserialize(const std::string&);
    private:
        std::regex file_name_regex_ = std::regex(R"([\w\.]+$)");
    };
}