#include "cpu.hpp"
#include "binSerializer.hpp"

int main(int argc, char* argv[]){
//    cpu_emulator::Cpu cpu;
//    if (argc == 2) {
//        cpu.setFilePath(argv[1]);
//        cpu.exec();
//    }
    cpu_emulator::Serializer serializer;
    serializer.serialize(argv[1]);

    cpu_emulator::Cpu cpu;
    cpu.execBinary(std::string(argv[1]) + ".bin");
}