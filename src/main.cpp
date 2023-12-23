#include "CHIP-8.h"
#include <iostream>


int main(int argc, char* argv[])
{
   //TODO: Work program to point where I can load ROM
   //remove void casts on command arguments
   static_cast<void>(argc);
   static_cast<void>(argv);

   //CHIP-8 system initialization
   Chip_8 system{};

   LoadFont(system);

   for (unsigned int i = FONTSET_START; i <= FONTSET_END; ++i)
   {
      std::cout << std::hex << static_cast<unsigned int>(system.memory.at(i)) << '\n';
   }

   std::cout
      << std::dec << '\n' << FONTSET_SIZE << '\n'
      << system.memory.at(FONTSET_START) << '\n'
      << system.pc << '\n'
      << system.memory.at(FONTSET_END) << '\n'
      << system.delayTimer << '\n' << system.opcode << '\n';

   return 0;
}