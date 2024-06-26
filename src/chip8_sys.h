#ifndef CHIP8_SYS_H
#define CHIP8_SYS_H

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define FONTSET_SIZE 80
#define PC_START 0x200
#define RAM_START 0x000
#define RAM_END 0X1FF
#define TOTAL_RAM 4096
#define STACK_SIZE 16
#define V_REGISTERS 16

#define NIBBLE1 0xF000
#define NIBBLE2 0x0F00
#define NIBBLE3 0x00F0
#define NIBBLE4 0x000F
#define FIRST_BYTE 0xFF00
#define LAST_BYTE 0x00FF
#define NNN 0x0FFF

#include <stdint.h>
#include <stdbool.h>


typedef struct Chip8_t
{
    uint8_t ram[TOTAL_RAM];
    uint16_t stack[STACK_SIZE];
    uint8_t keys[16];

    // Registers
    uint8_t vReg[V_REGISTERS];
    uint16_t index;
    uint16_t progCounter;
    int stackPointer;

    // Timers
    uint8_t delayTimer;
    uint8_t soundTimer;

    uint16_t opcode;

    bool screen[SCREEN_HEIGHT][SCREEN_WIDTH];

    bool isRunning;


} Chip8;

#endif // !CHIP8_SYS_H
