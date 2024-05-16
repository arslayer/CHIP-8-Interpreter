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

uint16_t jump_1nnn(const uint16_t address)
{
    return address;
}

uint8_t setRegVX_6xnn(const uint8_t value)
{
    return value;
}

void addVX_7xnn(Chip8* sys, const uint8_t reg, const uint8_t value)
{
    sys->vReg[reg] += value;
}

uint16_t setIndexReg_annn(const uint16_t index)
{
    return index;
}

void display_dxyn(Chip8* sys, uint8_t x, uint8_t y, uint8_t n)
{
    // Local variables
    int xPos = sys->vReg[x] & 64;
    int yPos = sys->vReg[y] & 32;
    sys->vReg[0xF] = 0;
    int spriteHeight = n;
    int pixel;
    bool screenPixel;

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

                screenPixel = sys->screen[yPos + i][xPos + j];

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
