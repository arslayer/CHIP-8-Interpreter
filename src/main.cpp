#include "CHIP-8.h"
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

   for(unsigned int i = FONTSET_START; i <= FONTSET_END; ++i)
   {
      std::cout 
         << std::hex << static_cast<unsigned int>(system.memory.at(i)) << '\n';
   }

   for(unsigned int i = START_ADDRESS; i < system.memory.size(); ++i)
   {
      if (system.memory.at(i) == 0){}
      else
      {
         std::cout 
            << std::hex << static_cast<unsigned int>(system.memory.at(i)) 
            << '\n';
      }
   }

   std::cout
      << std::dec << '\n' << FONTSET_SIZE << '\n'
      << system.memory.at(FONTSET_START) << '\n'
      << system.pc << '\n'
      << system.memory.at(FONTSET_END) << '\n'
      << system.delayTimer << '\n' << system.opcode << '\n';

   return 0;
}