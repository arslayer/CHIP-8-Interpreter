#include "CHIP-8.h"
#include <fstream>
#include <iostream>

//Function definitions

//Loads font set into memory at 0x50 to 0x9f
void LoadFont(Chip_8& system)
{
   for 
      (std::vector<uint8_t, std::allocator<uint8_t>>::size_type
      i{ 0 }; i < FONTSET_SIZE; ++i)
   {
      system.memory.at(FONTSET_START + i) = chip8_fontset.at(i);
   }
}

//Loads program into memory starting at 0x200
void LoadRom(Chip_8& system, std::string_view file)
{
   printf("Rom Loading Function\n");
}