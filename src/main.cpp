#include "CHIP-8.h"
#include "SDL.h"
#include <iostream>


int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      std::cout
         << "Usage: CHIP-8 <(path to)rom name>\n";
      
      return 1;
   }

   //Get rom file from cmd line argument
   std::string romName{ argv[1] };


   //CHIP-8 system initialization
   Chip_8 system{};

   //Load the font
   LoadFont(system);

   //Load rom
   LoadRom(system, romName);

   Fetch(system);

   std::cout
      << std::dec << '\n' << fontsetSize << '\n'
      << system.memory.at(fontsetStart) << '\n'
      << system.pc << '\n'
      << system.delayTimer << '\n' << system.opcode << '\n';

   return 0;
}