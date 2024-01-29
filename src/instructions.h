#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "chip8_sys.h"

uint16_t JMP(const uint16_t *address);
uint8_t LoadRegister(const uint8_t *value);
uint16_t LoadIndex(const uint16_t *index);
//void DrawSprite(Chip8 *sys);
//void ClearScreen(Chip8 *sys);

#endif // !INSTRUCTIONS_H
