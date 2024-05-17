#include "CHIP-8.h"
#include "raylib.h"
#include <stdio.h>

int main(void)
{
    /*if (argc != 2)
    {
        printf("Usage: CHIP-8 <(path to)rom name>\n");
      
        return 1;
    }*/

    //Get rom file from cmd line argument
    char* romName = "C:/Users/_ars_/source/repos/CHIP-8-Interpreter/1-chip8-logo.ch8";


    // CHIP-8 system declaration
    Chip8 system = *sysInit(romName);

    printf("Hi %x\n", system.ram[516]);
    while (true)
    {

        /*Fetch(&system);

        DecodeAndExecute(&system);*/
    }

    return 0;
}