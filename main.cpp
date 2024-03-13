#include "cpu.hpp"

int main(int argc, char* argv[]){
    cpu_emulator::Cpu cpu;
    if (argc == 2) {
        cpu.setFilePath(argv[1]);
        cpu.exec();
    }
}