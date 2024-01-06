#include "CHIP-8.h"
#include "chip8_sys.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: CHIP-8 <(path to)rom name>\n");
      
        return 1;
    }

    //Get rom file from cmd line argument
    char *romName = argv[1];


    // CHIP-8 system declaration
    Chip8 system = { .progCounter = PC_START };

    // Initialize the system
    //Init(&system);

    LoadRom(&system, romName);

    printf("Hi %x\n", system.ram[516]);

    /*std::cout
        << std::dec << '\n' << fontsetSize << '\n'
        << system.memory.at(fontsetStart) << '\n'
        << system.pc << '\n'
        << system.delayTimer << '\n' << system.opcode << '\n';*/
    return 0;
}