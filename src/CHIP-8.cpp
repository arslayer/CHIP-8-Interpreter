#include "CHIP-8.h"
#include <fstream>
#include <iostream>
#include <memory>

//Function definitions

//Loads font set into memory at 0x50 to 0x9f
void LoadFont(Chip_8& system)
{
   for 
      (std::vector<uint8_t, std::allocator<uint8_t>>::size_type i{ 0 };
       i < fontsetSize; ++i)
   {
      system.memory.at(fontsetStart + i) = chip8_fontset.at(i);
   }
}

//Loads program into memory starting at 0x200
void LoadRom(Chip_8& system, const std::string& file)
{
   std::ifstream rom(file, std::ios::binary | std::ios::ate);

   std::streampos size{ rom.tellg() };
   std::uint16_t romLen{ static_cast<uint16_t>(size) };
   
   std::unique_ptr<char[]> buffer{ std::make_unique<char[]>(romLen) };

   rom.seekg(0, std::ios::beg);
   rom.read(buffer.get(), size);
   rom.close();

   for 
      (size_t i{ 0 }; i < romLen; ++i)
   {
      system.memory.at(startAddress + i) 
         = static_cast<std::uint8_t>(buffer[i]);
   }
}

void Fetch(Chip_8& system)
{
   system.opcode 
      = static_cast<uint16_t>
      ((system.memory.at(system.pc) << 8u | system.memory.at(system.pc + 1u)));

   system.pc += 2;
}