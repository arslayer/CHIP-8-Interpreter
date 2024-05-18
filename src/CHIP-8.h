#ifndef CHIP8_H
#define CHIP8_H

#include "chip8_sys.h"


// Function Declarations

//void FontInit(Chip8 *sys);
//void LoadRom(Chip8 *sys, const char *rom);   
//void Fetch(Chip8 *sys);
//void DecodeAndExecute(Chip8 *sys);

Chip8* sysInit(const char *rom);

void cycle(Chip8* sys);

#endif