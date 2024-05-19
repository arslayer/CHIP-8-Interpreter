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

// Skip if value in VX is equal to NN
void skip_3xnn(Chip8* sys, const uint8_t x, const uint8_t nn);

// Skip if value in VX is not equal to NN
void skip_4xnn(Chip8* sys, const uint8_t x, const uint8_t nn);

// Skip if value in VX is equal to VY
void skip_5xy0(Chip8* sys, const uint8_t x, const uint8_t y);

// Sets the register V[X] to the value NN
uint8_t setRegVX_6xnn(const uint8_t value);

// Adds value NN to V[X]
void addVX_7xnn(Chip8 *sys, const uint8_t reg, const uint8_t value);


/* LOGIC AND ARITHMETIC INSTRUCTIONS */

// Set VX to the value of VY
void set_8xy0(Chip8* sys, const uint8_t x, const uint8_t y);

// Set VX to the bitwise OR of VX and VY
void binaryOR_8xy1(Chip8* sys, const uint8_t x, const uint8_t y);

// Set VX to the bitwise AND of VX and VY
void binaryAND_8xy2(Chip8* sys, const uint8_t x, const uint8_t y);

// Set VX to the bitwise XOR of VX and VY
void logicalXOR_8xy3(Chip8* sys, const uint8_t x, const uint8_t y);

// Add VY to VX and set carry flag VF if overflow
void add_8xy4(Chip8* sys, const uint8_t x, const uint8_t y);

// Set VX to VX minus VY and set carry flag
void sub_8xy5(Chip8* sys, const uint8_t x, const uint8_t y);

// Shift right
void shiftRight_8xy6(Chip8* sys, const uint8_t x, const uint8_t y);

// Set VX to VY - VX and set carry flag
void sub_8xy7(Chip8* sys, const uint8_t x, const uint8_t y);

// Shift left
void shiftLeft_8xye(Chip8* sys, const uint8_t x, const uint8_t y);

/* LOGIC AND ARITHMETIC END */


// Skip if value in VX is not equal to VY
void skip_9xy0(Chip8* sys, const uint8_t x, const uint8_t y);

// Sets the index register to value NNN
uint16_t setIndexReg_annn(const uint16_t index);

// Jump with offset
void jumpOffset_bnnn(Chip8* sys, const uint16_t nnn);

// Store random number in VX
void random_cxnn(Chip8* sys, const uint8_t x, const uint8_t nn);

// Turns pixels on to be drawn to screen.
void display_dxyn(Chip8 *sys, uint8_t x, uint8_t y, uint8_t n);


/* SKIP IF KEY */

// Skip if key corresponding to VX is pressed
void skipIfPressed_ex9e(Chip8* sys, const uint8_t x);

// Skip if key corresponding to VX is not pressed
void skipIfNotPressed_exa1(Chip8* sys, const uint8_t x);

/* END SKIP IF KEY */


/* TIMERS */

// Set VX to delay timer value
void setVXDelay_fx07(Chip8* sys, const uint8_t x);

// Set delay timer to value in VX
void setDelay_fx15(Chip8* sys, const uint8_t x);

// Set sound timer to value in VX
void setSound_fx18(Chip8* sys, const uint8_t x);

/* END TIMERS */


// Add VX value to index
void addToIndex_fx1e(Chip8* sys, const uint8_t x);

// Get key that is pressed
void getKey_fx0a(Chip8* sys, const uint8_t x);

// Set index at address of font character
void font_fx29(Chip8* sys, const uint8_t x);

// Binary-coded decimal conversion
void bcd_fx33(Chip8* sys, const uint8_t x);

// Store memory from registers
void storeMem_fx55(Chip8* sys, const uint8_t x);

// Load memory to registers
void loadMem_fx65(Chip8* sys, const uint8_t x);

#endif // !INSTRUCTIONS_H
