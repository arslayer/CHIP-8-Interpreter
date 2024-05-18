#include "CHIP-8.h"
#include "instructions.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Function definitions

// Loads font set into memory at
static void FontInit(Chip8 *sys)
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


   for (int i = 0; i < FONTSET_SIZE; i++) {
      sys->ram[i] = fontSet[i];
   }
}

// Fetch opcode from memory
static void Fetch(Chip8 *sys)
{
    // Local variable to access array
    const uint16_t pc = sys->progCounter;

    // Get opcode from bytes stored at memory locations
    sys->opcode = (sys->ram[pc] << 8 | sys->ram[pc + 1]);

    // Increment the program counter by 2 for next instruction
    sys->progCounter += 2;
}



// Loads program into memory starting at 0x200
static void LoadRom(Chip8 *sys, const char *rom)
{
    FILE *fp = fopen(rom, "rb");

    if (fp != NULL)
    { 

        fseek(fp, 0, SEEK_END);
        const size_t romLength = ftell(fp);
        rewind(fp);

        uint8_t *buffer = malloc(sizeof(uint8_t) * romLength);

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
        
        free(buffer);

        buffer = NULL;
    }
    else
    {
        printf("ERROR: ROM file not found\n");
        exit(EXIT_FAILURE);
    }

    fclose(fp);
    
}

static void DecodeAndExecute(Chip8* sys)
{
    // Local opcode variable
    uint16_t opcode = sys->opcode;

    // Extract values from opcode with bitmasks.
    uint8_t instruction = (opcode & NIBBLE1) >> 12U;
    uint8_t regX = (opcode & NIBBLE2) >> 8U;
    uint8_t regY = (opcode & NIBBLE3) >> 4U;
    uint8_t n = (opcode & NIBBLE4);
    uint8_t doubleN = (opcode & LAST_BYTE);
    /*uint8_t firstByte = (opcode & FIRST_BYTE) >> 8U;*/
    uint16_t tripleN = (opcode & NNN);

    switch (instruction)
    {
    case 0x0:
        switch (doubleN)
        {
        case 0xE0:
            clearScreen_00e0(sys);
            break;
        default:
            break;
        }
        break;
    case 0x1:
        sys->progCounter = jump_1nnn(tripleN);
        break;
    case 0x6:
        sys->vReg[regX] = setRegVX_6xnn(doubleN);
        break;
    case 0x7:
        addVX_7xnn(sys, regX, doubleN);
        break;
    case 0xA:
        sys->index = setIndexReg_annn(tripleN);
        break;
    case 0xD:
        display_dxyn(sys, regX, regY, n);
        break;
    default:
        break;
    }
}

// Initialize the Chip8 system
Chip8* sysInit(const char *rom)
{ 
    // Allocate memory for struct to be returned
    Chip8 *temp = calloc(1, sizeof(Chip8));
    
    if (temp != NULL) {
        // Initialize struct members
        temp->isRunning = true;
        temp->progCounter = PC_START;
        temp->drawScreen = false;

        // Load font
        FontInit(temp);

        // Load rom
        LoadRom(temp, rom);
        
    }
    else {
        printf("Memory not allocated");
    }

    return temp;
    
}

void cycle(Chip8* sys)
{
    Fetch(sys);
    DecodeAndExecute(sys);
}
