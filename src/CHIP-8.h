#ifndef CHIP8_H
#define CHIP8_H

#include "chip8_sys.h"


// Function Declarations
void Init(Chip8 *sys);
void LoadRom(Chip8 *sys, char *rom);   
void Fetch(Chip8 *sys);                              

#endif