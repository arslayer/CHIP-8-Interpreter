#include "instructions.h"
#include "raylib.h"

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
    
    // Add value in VY to VX
    sys->vReg[x] += sys->vReg[y];

    // Set VF to 1 if result is greater than 255
    if (result > 255) {
        sys->vReg[0xF] = 1;
    }
    else {
        sys->vReg[0xF] = 0;
    }
}

void sub_8xy5(Chip8* sys, const uint8_t x, const uint8_t y)
{
    uint8_t minuend = sys->vReg[x];
    uint8_t subtrahend = sys->vReg[y];

    // Perform subtraction and store in VX
    sys->vReg[x] = sys->vReg[x] - sys->vReg[y];

    // Check if VX is greater than VY and set carry flag to 1 if true
    if (minuend >= subtrahend) {
        sys->vReg[0xF] = 1;
    }
    // Set to zero if not true
    else {
        sys->vReg[0xF] = 0;
    }
}

void shiftRight_8xy6(Chip8* sys, const uint8_t x, const uint8_t y)
{
    // Set VX to value of VY
    sys->vReg[x] = sys->vReg[y];

    // Get bit that will be shifted out
    bool bit = sys->vReg[x] & 0x01;

    // Shift value
    sys->vReg[x] >>= 0x01;

    // Set carry flag depending on bit shifted out
    if (bit) {
        sys->vReg[0xF] = 1;
    }
    else {
        sys->vReg[0xF] = 0;
    }
}

void sub_8xy7(Chip8* sys, const uint8_t x, const uint8_t y)
{
    uint8_t minuend = sys->vReg[y];
    uint8_t subtrahend = sys->vReg[x];

    // Perform subtraction and store in VX
    sys->vReg[x] = sys->vReg[y] - sys->vReg[x];
    
    // Check if VY is greater than VX and set carry flag to 1 if true
    if (minuend >= subtrahend) {
        sys->vReg[0xF] = 1;
    }
    // Set to zero if not true
    else {
        sys->vReg[0xF] = 0;
    }
}

void shiftLeft_8xye(Chip8* sys, const uint8_t x, const uint8_t y)
{
    // Set VX to value of VY
    sys->vReg[x] = sys->vReg[y];

    // Get bit that will be shifted out
    bool bit = (sys->vReg[x] & 0x80);

    // Shift value
    sys->vReg[x] <<= 0x01;

    // Set carry flag depending on bit shifted out
    if (bit) {
        sys->vReg[0xF] = 1;
    }
    else {
        sys->vReg[0xF] = 0;
    }
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

void jumpOffset_bnnn(Chip8* sys, const uint16_t nnn)
{
    sys->progCounter = nnn + sys->vReg[0];
}

void random_cxnn(Chip8* sys, const uint8_t x, const uint8_t nn)
{
    sys->vReg[x] = GetRandomValue(0, nn) & nn;
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

void skipIfPressed_ex9e(Chip8* sys, const uint8_t x)
{
    if (IsKeyDown(sys->keys[sys->vReg[x]])) {
        sys->progCounter += 2;
    }
}

void skipIfNotPressed_exa1(Chip8* sys, const uint8_t x)
{
    if (IsKeyUp(sys->keys[sys->vReg[x]])) {
        sys->progCounter += 2;
    }
}

void setVXDelay_fx07(Chip8* sys, const uint8_t x)
{
    sys->vReg[x] = sys->delayTimer;
}

void setDelay_fx15(Chip8* sys, const uint8_t x)
{
    sys->delayTimer = sys->vReg[x];
}

void setSound_fx18(Chip8* sys, const uint8_t x)
{
    sys->soundTimer = sys->vReg[x];
}

void addToIndex_fx1e(Chip8* sys, const uint8_t x)
{
    // Get result of addition to check for overflow
    /*int result = sys->index + sys->vReg[x];*/

    // Perform addition
    sys->index += sys->vReg[x];

    // Set VF register to 1 if result outside of mem range
    /*if (result > 0xFFF) {
        sys->vReg[0xF] = 1;
    }*/

}

void getKey_fx0a(Chip8* sys, const uint8_t x)
{
    // Set flag to see if any keys have been pressed AND released
    bool notPressed = true;

    // Loop through keypad
    for (int i = 0; i < 16; i++) {
        // See if key has been released once
        if (IsKeyReleased(sys->keys[i])) {

            // Set VX to keypad number
            sys->vReg[x] = (uint8_t)i;

            // Set flag to false
            notPressed = false;

            // break from loop
            break;
        }
    }

    // Decrement program counter if no keys were pressed.
    if (notPressed) {
        sys->progCounter -= 2;
    }
}

void font_fx29(Chip8* sys, const uint8_t x)
{
    // Font sprites start at every 5th mem address from zero.
    sys->index = sys->vReg[x] * 5;
}

void bcd_fx33(Chip8* sys, const uint8_t x)
{
    // Separate value of VX into 3 digits
    uint8_t hundreds = sys->vReg[x] / 100;
    uint8_t tens = (sys->vReg[x] / 10) % 10;
    uint8_t ones = (sys->vReg[x] % 100) % 10;

    // Store at memory locations
    sys->ram[sys->index] = hundreds;
    sys->ram[sys->index + 1] = tens;
    sys->ram[sys->index + 2] = ones;
}

void storeMem_fx55(Chip8* sys, const uint8_t x)
{
    // Test if x is 0
    if (x == 0) {
        // Store V0 into memory at index
        sys->ram[sys->index] = sys->vReg[0];
    }
    // Loop and store if greater than 0
    else {
        for (int i = 0; i <= x; i++) {
            sys->ram[sys->index + i] = sys->vReg[i];
        }
    }
}

void loadMem_fx65(Chip8* sys, const uint8_t x)
{
    // Test if x is 0
    if (x == 0) {
        // Load memory from index into V0
        sys->vReg[0] = sys->ram[sys->index];
    }
    // Loop and load if greater than 0
    else {
        for (int i = 0; i <= x; i++) {
            sys->vReg[i] = sys->ram[sys->index + i];
        }
    }
}
