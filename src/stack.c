#include "stack.h"
#include <stdio.h>

bool isEmpty(const Stack* stk)
{
    return (stk->size == 0);
}

void push(Stack* stk, uint16_t val)
{
    if (stk->size != STACK_SIZE) {
        stk->stack[stk->size++] = val;
    }
    else {
        printf("Stack is full");
        return 1;
    }
}

uint16_t pop(Stack* stk)
{
    if (!(isEmpty(stk))) {
        uint16_t temp = stk->stack[--stk->size];
        return temp;
    }
    else {
        printf("Stack is empty");
        return 1;
    }
}
