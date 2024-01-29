#include "CHIP-8.h"
#include "instructions.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Function definitions

// Loads font set into memory at 0x50 to 0x9f
void LoadFont(Chip8 *sys)
{
    // Chip-8 fontset to be loaded into memory.
    static const uint8_t fontSet[FONTSET_SIZE] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xf0, 0x90, 0xf0, // 6
        0xf0, 0x10, 0x20, 0x40, 0x40, // 7
        0xf0, 0x90, 0xf0, 0x90, 0xf0, // 8
        0xf0, 0x90, 0xf0, 0x10, 0xf0, // 9
        0xf0, 0x90, 0xf0, 0x90, 0x90, // A
        0xe0, 0x90, 0xe0, 0x90, 0xe0, // B
        0xf0, 0x80, 0x80, 0x80, 0xf0, // C
        0xe0, 0x90, 0x90, 0x90, 0xe0, // D
        0xF0, 0x80, 0xf0, 0x80, 0xf0, // E
        0xF0, 0x80, 0xf0, 0x80, 0x80  // F
    };


   for (int i = FONTSET_START, j = 0; i <= FONTSET_END &&
       j < FONTSET_SIZE; i++, j++)
   {
      sys->ram[i] = fontSet[j];
   }
}

// Fetch opcode from memory
void Fetch(Chip8 *sys)
{
    // Local variable to access array
    uint16_t pc = sys->progCounter;

    // Get opcode from bytes stored at memory locations
    sys->opcode = (sys->ram[pc] << 8 | sys->ram[pc + 1]);

    // Increment the program counter by 2 for next instruction
    sys->progCounter += 2;
}



// Loads program into memory starting at 0x200
void LoadRom(Chip8 *sys, const char *rom)
{
    uint8_t *buffer;
    FILE *fp = fopen(rom, "rb");

    if (fp != NULL)
    { 

        fseek(fp, 0, SEEK_END);
        size_t romLength = ftell(fp);
        rewind(fp);

        buffer = malloc(sizeof(uint8_t) * romLength);

        if (buffer == NULL)
        {
            printf("ERROR: Out of memory\n");
            exit(EXIT_FAILURE);
        }
        
        fread(buffer, sizeof(uint8_t), romLength, fp);

        for (int i = 0; i < romLength; i++)
        {
            sys->ram[PC_START + i] = buffer[i];
        }
        
    }
    else
    {
        printf("ERROR: ROM file not found\n");
        exit(EXIT_FAILURE);
    }

    fclose(fp);
    free(buffer);
}

void DecodeAndExecute(Chip8* sys)
{
    // Local opcode variable
    uint16_t opcode = sys->opcode;

    // Extract values from opcode with bitmasks.
    uint8_t instruction = (opcode & NIBBLE1) >> 12U;
    uint8_t regX = (opcode & NIBBLE2) >> 8U;
    uint8_t regY = (opcode & NIBBLE3) >> 4U;
    uint8_t n = (opcode & NIBBLE4);
    uint8_t doubleN = (opcode & LAST_BYTE);
    uint8_t firstByte = (opcode & FIRST_BYTE) >> 8U;
    uint16_t tripleN = (opcode & NNN);

    switch (instruction)
    {
    case 0x0:
        switch (doubleN)
        {
        case 0xE0:
            //TODO: Clear the screen and set draw flag
            printf("Cleared the screen\n");
            break;
        default:
            break;
        }
        break;
    case 0x1:
        sys->progCounter = JMP(&tripleN);
        break;
    case 0x6:
        sys->vReg[regX] = LoadRegister(&doubleN);
        break;
    case 0xA:
        sys->index = LoadIndex(&tripleN);
        break;
    case 0xD:
        //TODO: Draw sprite to screen and set draw flag
        printf("Drawing sprite\n");
        break;
    default:
        break;
    }
    printf("%x\n%x\n%x\n%x\n%x\n%x\n%x\n\n", instruction, regX, regY, n, doubleN, firstByte, tripleN);
}