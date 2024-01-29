#include "instructions.h"

uint16_t JMP(const uint16_t* address)
{
    return *address;
}

uint16_t LoadIndex(const uint16_t* index)
{
    return *index;
}

uint8_t LoadRegister(const uint8_t* value)
{
    return *value;
}