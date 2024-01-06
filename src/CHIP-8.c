#include "CHIP-8.h"
#include "chip8_sys.h"
#include <stdint.h>
#include <string.h>

// Function definitions

// Loads font set into memory at 0x50 to 0x9f
static void LoadFont(Chip8 *sys)
{
    // Chip-8 fontset to be loaded into memory.
    static const uint8_t fontSet[FONTSET_SIZE] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xf0, 0x90, 0xf0, // 6
        0xf0, 0x10, 0x20, 0x40, 0x40, // 7
        0xf0, 0x90, 0xf0, 0x90, 0xf0, // 8
        0xf0, 0x90, 0xf0, 0x10, 0xf0, // 9
        0xf0, 0x90, 0xf0, 0x90, 0x90, // A
        0xe0, 0x90, 0xe0, 0x90, 0xe0, // B
        0xf0, 0x80, 0x80, 0x80, 0xf0, // C
        0xe0, 0x90, 0x90, 0x90, 0xe0, // D
        0xF0, 0x80, 0xf0, 0x80, 0xf0, // E
        0xF0, 0x80, 0xf0, 0x80, 0x80  // F
    };


   for (int i = FONTSET_START, j = 0; i <= FONTSET_END &&
       j < FONTSET_SIZE; i++, j++)
   {
      sys->ram[i] = fontSet[j];
   }
}


// Chip-8 system initialization
void Init(Chip8 *sys)
{
    *sys = (Chip8)
    {
        .progCounter = PC_START,
    };

    LoadFont(sys);
};





//Loads program into memory starting at 0x200
/*void LoadRom(Chip8* sys, char* rom)
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
*/
