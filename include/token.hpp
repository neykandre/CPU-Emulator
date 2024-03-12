#pragma once
#include <string>
#include <vector>
#include "settings.hpp"

namespace cpu_emulator {
    enum class commandType {
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
        ret,
        label,
        begin,
        end,
        unknown
    };

    struct ParsedLine {
        commandType type{commandType::unknown};
        std::vector<std::string> args;
    };
}