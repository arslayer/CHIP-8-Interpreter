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
    Chip8 system = { .progCounter = PC_START,
                     .isRunning = true,
                     .drawScreen = false };

    // Load the font
    LoadFont(&system);

    LoadRom(&system, romName);

    printf("Hi %x\n", system.ram[516]);

    DecodeAndExecute(&system);

    return 0;
}