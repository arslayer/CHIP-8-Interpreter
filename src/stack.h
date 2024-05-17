#ifndef STACK_H
#define STACK_H

#include "chip8_sys.h"
#include <stdint.h>

typedef struct Stack_t {
    uint16_t stack[STACK_SIZE];
    int size;
} Stack;

bool isEmpty(const Stack* stk);

void push(Stack* stk, uint16_t val);

uint16_t pop(Stack* stk);


#endif // STACK_H