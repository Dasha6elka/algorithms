#ifndef ALGORITHMS_STACK_H
#define ALGORITHMS_STACK_H

#include <string>
#include <vector>

typedef char *TStackItem;

typedef struct
{
    TStackItem *items;
    TStackItem top;
    size_t size;
} Stack;

Stack *CreateStack();

void StackDestroy(Stack *p_stack);

bool StackIsEmpty(Stack *p_stack);

void StackPush(Stack *p_stack, TStackItem element);

TStackItem StackPop(Stack *p_stack);

std::vector<int> StackFind(Stack *p_stack, char *str);

void RemoveElement(Stack *p_stack, std::vector<int> positions);

#endif //ALGORITHMS_STACK_H
