#include "../include/cpu.hpp"

namespace cpu_emulator {

    void Cpu::setFilePath(const std::string& path) {
        file_path_ = path;
    }

    void Cpu::setFilePath(std::string&& path) {
        file_path_ = std::move(path);
    }

    void Cpu::exec() {
        Preprocessor preprocessor;

    }
}