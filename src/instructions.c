#include "instructions.h"

void clearScreen_00e0(Chip8* sys)
{
    // Loop through screen 2D array and set pixels off
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            sys->screen[i][j] = false;
        }
    }

    // Set drawScreen flag to false
    sys->drawScreen = true;
}

void return_00ee(Chip8* sys)
{
    sys->progCounter = sys->stack[--sys->stackPointer];
}

uint16_t jump_1nnn(const uint16_t address)
{
    return address;
}

void call_2nnn(Chip8* sys, const uint16_t nnn)
{
    sys->stack[sys->stackPointer++] = sys->progCounter;
    sys->progCounter = nnn;
}

void skip_3xnn(Chip8* sys, const uint8_t x, const uint8_t nn)
{
    if (sys->vReg[x] == nn) {
        sys->progCounter += 2;
    }
}

void skip_4xnn(Chip8* sys, const uint8_t x, const uint8_t nn)
{
    if (sys->vReg[x] != nn) {
        sys->progCounter += 2;
    }
}

void skip_5xy0(Chip8* sys, const uint8_t x, const uint8_t y)
{
    if (sys->vReg[x] == sys->vReg[y]) {
        sys->progCounter += 2;
    }
}

uint8_t setRegVX_6xnn(const uint8_t value)
{
    return value;
}

void addVX_7xnn(Chip8* sys, const uint8_t reg, const uint8_t value)
{
    sys->vReg[reg] += value;
}

void set_8xy0(Chip8* sys, const uint8_t x, const uint8_t y)
{
    sys->vReg[x] = sys->vReg[y];
}

void binaryOR_8xy1(Chip8* sys, const uint8_t x, const uint8_t y)
{
    sys->vReg[x] |= sys->vReg[y];
}

void binaryAND_8xy2(Chip8* sys, const uint8_t x, const uint8_t y)
{
    sys->vReg[x] &= sys->vReg[y];
}

void logicalXOR_8xy3(Chip8* sys, const uint8_t x, const uint8_t y)
{
    sys->vReg[x] ^= sys->vReg[y];
}

void add_8xy4(Chip8* sys, const uint8_t x, const uint8_t y)
{
    // Get result to test for "overflow"
    int result = sys->vReg[x] + sys->vReg[y];
    
    // Set VF to 1 if result is greater than 255
    if (result > 255) {
        sys->vReg[0xF] = 1;
    }

    // Add value in VY to VX
    sys->vReg[x] += sys->vReg[y];
}

void sub_8xy5(Chip8* sys, const uint8_t x, const uint8_t y)
{
    // Check if VX is greater than VY and set carry flag to 1 if true
    if (sys->vReg[x] > sys->vReg[y]) {
        sys->vReg[0xF] = 1;
    }
    // Set to zero if not true
    else {
        sys->vReg[0xF] = 0;
    }

    // Perform subtraction and store in VX
    sys->vReg[x] = sys->vReg[x] - sys->vReg[y];
}

void sub_8xy7(Chip8* sys, const uint8_t x, const uint8_t y)
{
    // Check if VY is greater than VX and set carry flag to 1 if true
    if (sys->vReg[y] > sys->vReg[x]) {
        sys->vReg[0xF] = 1;
    }
    // Set to zero if not true
    else {
        sys->vReg[0xF] = 0;
    }

    // Perform subtraction and store in VX
    sys->vReg[x] = sys->vReg[y] - sys->vReg[x];
}

void skip_9xy0(Chip8* sys, const uint8_t x, const uint8_t y)
{
    if (sys->vReg[x] != sys->vReg[y]) {
        sys->progCounter += 2;
    }
}

uint16_t setIndexReg_annn(const uint16_t index)
{
    return index;
}

void display_dxyn(Chip8* sys, uint8_t x, uint8_t y, uint8_t n)
{
    // Local variables
    int xPos = sys->vReg[x] % 64;
    int yPos = sys->vReg[y] % 32;
    sys->vReg[0xF] = 0;
    int spriteHeight = n;
    int pixel;

    // Outer loop for y axis
    for (int i = 0; i < spriteHeight; i++) {

        // Get pixel in memory if not at edge of screen
        if ((yPos + i) < 32) {
            pixel = sys->ram[sys->index + i];
        }
        else {
            break;
        }

        // Inner loop for x axis
        for (int j = 0; j < 8; j++) {

            // Check if within screen bounds
            if ((xPos + j) < 64) {

                if (!(pixel >> (7 - j) & 0x1)) {
                    continue;
                }

                bool screenPixel = sys->screen[yPos + i][xPos + j];

                if (screenPixel) {
                    sys->vReg[0xF] = 1;
                }

                sys->screen[yPos + i][xPos + j] ^= true;
            }
            else {
                break;
            }
        }
    }
    // Set drawScreen flag to true
    sys->drawScreen = true;
}
