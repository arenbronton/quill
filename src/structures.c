#include <stdbool.h>
#include "structures.h"

Stack *create_stack(int capacity)
{
    if (capacity <= 0)
        return NULL;

    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL)
        return NULL;

    stack->collection = malloc(sizeof(char) * capacity);
    if (stack->collection == NULL)
    {
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->size = 0;

    return stack;
}

void destroy_stack(Stack *stack)
{
    free(stack->collection);
    free(stack);
}

bool is_full(Stack *stack)
{
    return stack->capacity == stack->size;
}

bool is_empty(Stack *stack)
{
    return stack->size == 0;
}

bool push(Stack *stack, char item)
{
    if (is_full(stack))
        return false;

    stack->collection[stack->size] = item;
    stack->size++;

    return true;
}

bool peek(Stack *stack, char *item)
{
    if (is_empty(stack))
        return false;

    *item = stack->collection[stack->size - 1];

    return true;
}

bool pop_ignore(Stack *stack)
{
    if (is_empty(stack))
        return false;

    stack->size--;

    return true;
}

bool pop(Stack *stack, char *item)
{
    if (is_empty(stack))
        return false;

    stack->size--;
    *item = stack->collection[stack->size];

    return true;
}