#include <iostream>
#include "cpu.hpp"
#include "binSerializer.hpp"

int main(int argc, char* argv[]){
    if (argc == 3) {
        if (std::string(argv[1]) == "--mk_bin" || std::string(argv[1]) == "-mb") {
            cpu_emulator::Serializer::serialize(argv[2]);
        }
        else if (std::string(argv[1]) == "--run_bin" || std::string(argv[1]) == "-rb") {
            cpu_emulator::Cpu cpu;
            cpu.execBinary(argv[2]);
        }
        else if (std::string(argv[1]) == "--run_file" || std::string(argv[1]) == "-rf") {
            cpu_emulator::Cpu cpu;
            cpu.exec(argv[2]);
        }
        else {
            std::cout << "Unknown command code: " + std::string(argv[1]) << std::endl;
        }
    }
}