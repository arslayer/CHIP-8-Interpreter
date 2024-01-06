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
#define NUM_REGISTERS 16

#include <stdint.h>

typedef struct Chip8_sys Chip8;

const static uint8_t FONTSET[FONTSET_SIZE] =
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

struct Chip8_sys
{
    uint8_t ram[TOTAL_RAM];
    uint16_t stack[STACK_SIZE];

    // Registers
    uint8_t vReg[NUM_REGISTERS];
    uint16_t index;
    uint16_t progCounter;
    uint16_t stackPointer;

    // Timers
    uint8_t delayTimer;
    uint8_t soundTimer;

    uint16_t opcode;

    uint32_t screen[SCREEN_HEIGHT * SCREEN_WIDTH];


};
#endif // !CHIP8_SYS_H