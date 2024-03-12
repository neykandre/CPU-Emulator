#include <fstream>
#include "../include/preprocessor.hpp"


namespace cpu_emulator {
    void Preprocessor::setFilePath(const std::string& path) {
        file_path_ = path;
    }

    void Preprocessor::setFilePath(std::string&& path) {
        file_path_ = std::move(path);
    }

    void Preprocessor::setFromFile() {
        std::ifstream in(file_path_);
        Parser parser;
    }
}
