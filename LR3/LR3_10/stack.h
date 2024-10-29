#ifndef LR3_10_STACK_H
#define LR3_10_STACK_H

#include <stdlib.h>

typedef struct {
    void **buffer;
    size_t len;
    size_t capacity;
} Stack;

Stack *NewSack(size_t);

void Push(Stack *, void *);

void Pop(Stack *);

void *Peek(Stack *);

#endif
