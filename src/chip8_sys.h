#ifndef CHIP8_SYS_H
#define CHIP8_SYS_H

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define FONTSET_SIZE 80
#define PC_START 0x200
#define RAM_START 0x000
#define RAM_END 0X1FF
#define FONTSET_START 0x050
#define FONTSET_END 0x09F
#define TOTAL_RAM 4096
#define STACK_SIZE 16
#define V_REGISTERS 16

#define PIXEL_ON 0xFFFFFFFF
#define PIXEL_OFF 0x00000000

#define NIBBLE1 0xF000
#define NIBBLE2 0x0F00
#define NIBBLE3 0x00F0
#define NIBBLE4 0x000F
#define FIRST_BYTE 0xFF00
#define LAST_BYTE 0x00FF
#define NNN 0x0FFF

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint8_t ram[TOTAL_RAM];
    uint16_t stack[STACK_SIZE];

    // Registers
    uint8_t vReg[V_REGISTERS];
    uint16_t index;
    uint16_t progCounter;
    uint16_t stackPointer;

    // Timers
    uint8_t delayTimer;
    uint8_t soundTimer;

    uint16_t opcode;

    uint32_t screen[SCREEN_HEIGHT * SCREEN_WIDTH];

    bool isRunning;
    bool drawScreen;


} Chip8;

#endif // !CHIP8_SYS_H
