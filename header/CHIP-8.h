#ifndef CHIP8_H
#define CHIP8_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

//Globals

constexpr int SCREEN_WIDTH{ 64 };
constexpr int SCREEN_HEIGHT{ 32 };
constexpr int fontsetSize{ 0x50 };
constexpr int fontsetStart{ 0x50 };
constexpr unsigned int startAddress{ 0x200 };
constexpr std::uint16_t opMask{ 0xF000 };
constexpr std::uint16_t xMask{ 0x0F00 };
constexpr std::uint16_t yMask{ 0x00F0 };
constexpr std::uint16_t nMask{ 0x000F };
constexpr std::uint16_t nnnMask{ 0x0FFF };
constexpr std::uint16_t nnMask{ 0x00FF };

//Global array for font
constexpr std::array<std::uint8_t, fontsetSize> chip8_fontset
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

//alias template for 2d array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array <std::array<T, Col>, Row>;

//CHIP-8 Struct object

struct Chip_8
{
   Chip_8() : memory(4096), vRegister(16) {}
   std::vector<std::uint8_t> memory;      //4KB of memory
   std::vector<std::uint8_t> vRegister;   //registers
   std::vector<std::uint16_t> stack{};    //Stack
   std::uint16_t index{};                 //index pointer
   std::uint16_t pc{ startAddress };     //program counter
   std::uint8_t soundTimer{};             //sound timer
   std::uint8_t delayTimer{};             //delay timer
   std::uint16_t opcode{};                //opcode
   Array2d
      <std::uint32_t, SCREEN_HEIGHT,
       SCREEN_WIDTH> screen{};            //display
   bool isDrawing{ false };               //draw to screen flag
};

//Function Declarations

void LoadFont(Chip_8& system);                           //Loads system font
void LoadRom(Chip_8& system, const std::string& file);   //Loads rom
void Fetch(Chip_8& system);                              //fetch opcode

#endif