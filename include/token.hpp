#pragma once

#include <string>
#include <vector>
#include <variant>
#include "state.hpp"
#include "settings.hpp"

namespace cpu_emulator {
    enum class commandType : char {
        unknown,
        push,
        pop,
        pushR,
        popR,
        add,
        sub,
        mul,
        div,
        out,
        in,
        label,
        begin,
        end,
        jump,       // NOT CHANGEABLE ORDER
        jumpEq,     // NOT CHANGEABLE ORDER
        jumpNe,     // NOT CHANGEABLE ORDER
        jumpGr,     // NOT CHANGEABLE ORDER
        jumpGrEq,   // NOT CHANGEABLE ORDER
        jumpLes,    // NOT CHANGEABLE ORDER
        jumpLesEq,  // NOT CHANGEABLE ORDER
        call,       // NOT CHANGEABLE ORDER
        ret,
        eof
    };

    enum class argType {
        unknown,
        reg,
        value,
        label,
        label_idx
    };

    struct argToken {
        argType type{argType::unknown};
        std::string label;
        std::variant<enum_registers, value_type, size_t> arg;
    };

    struct Instruction {
        commandType type{commandType::unknown};
        std::vector<argToken> args;
        size_t line_pos;
        std::string src_string;
    };
}