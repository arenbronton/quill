#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    char *collection;
    int capacity;
    int size;
} Stack;

Stack *create_stack(int capacity);
void destroy_stack(Stack *stack);
bool is_full(Stack *stack);
bool is_empty(Stack *stack);

bool pop(Stack *stack, char *item);
bool pop_ignore(Stack *stack);
bool push(Stack *stack, char item);
bool peek(Stack *stack, char *item);