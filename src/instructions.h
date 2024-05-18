#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "chip8_sys.h"

// Turn all pixels off.
void clearScreen_00e0(Chip8 *sys);

// Return from subroutine
void return_00ee(Chip8* sys);

//  Sets program counter to NNN.  Program jumps to memory location
uint16_t jump_1nnn(const uint16_t address);

// Call subroutine at memory location NNN
void call_2nnn(Chip8* sys, const uint16_t nnn);

// Sets the register V[X] to the value NN
uint8_t setRegVX_6xnn(const uint8_t value);

// Adds value NN to V[X]
void addVX_7xnn(Chip8 *sys, const uint8_t reg, const uint8_t value);

// Sets the index register to value NNN
uint16_t setIndexReg_annn(const uint16_t index);

// Turns pixels on to be drawn to screen.
void display_dxyn(Chip8 *sys, uint8_t x, uint8_t y, uint8_t n);

#endif // !INSTRUCTIONS_H
