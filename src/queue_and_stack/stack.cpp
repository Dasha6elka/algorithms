#include <utility>
#include <string>
#include <cstring>
#include <vector>
#include <stdexcept>

#include "stack.h"

Stack *CreateStack()
{
    auto *p_stack = new Stack();
    p_stack->size = 0;
    p_stack->top = nullptr;
    p_stack->items = nullptr;
    return p_stack;
}

void StackDestroy(Stack *p_stack)
{
    delete[] p_stack->items;
    delete p_stack;
}

bool StackIsEmpty(Stack *p_stack)
{
    return p_stack->size == 0;
}

void StackPush(Stack *p_stack, TStackItem element)
{
    size_t size = p_stack->size * sizeof(TStackItem) + sizeof(TStackItem);
    if (StackIsEmpty(p_stack)) {
        p_stack->items = static_cast<TStackItem *>(malloc(size));
    } else {
        p_stack->items = static_cast<TStackItem *>(realloc(p_stack->items, size));
    }
    if (p_stack->items == nullptr) {
        throw std::overflow_error("Cannot allocate memory...");
    }
    p_stack->items[p_stack->size] = element;
    p_stack->top = element;
    p_stack->size++;

}

TStackItem StackPop(Stack *p_stack)
{
    if (StackIsEmpty(p_stack)) {
        throw std::underflow_error("Cannot pop from empty stack");
    }
    p_stack->size--;
    TStackItem last = p_stack->items[p_stack->size];
    size_t size = p_stack->size * sizeof(TStackItem);
    p_stack->items = static_cast<TStackItem *>(realloc(p_stack->items, size));
    return last;
}

void RemoveElement(Stack *p_stack, std::vector<int> positions)
{
    for (const auto &position : positions) {
        for (int i = position; i < p_stack->size; ++i) {
            p_stack->items[i] = p_stack->items[i + 1];
        }
        p_stack->size--;
        for (auto &pos : positions) {
            pos--;
        }
    }
    p_stack->top = p_stack->items[p_stack->size - 1];
    size_t size = p_stack->size * sizeof(TStackItem);
    p_stack->items = static_cast<TStackItem *>(realloc(p_stack->items, size));
}

std::vector<int> StackFind(Stack *p_stack, char *str)
{
    std::vector<int> positions;
    for (int i = 0; i < p_stack->size; ++i) {
        if (strcmp(p_stack->items[i], str) != 0) {
            continue;
        }
        positions.push_back(i);
    }
    return positions;
}
