#include "stack.h"

Stack *NewSack(size_t initialCapacity) {
    Stack *result = malloc(sizeof(Stack));
    if (!result) {
        return NULL;
    }
    void **buffer = malloc(sizeof(void *) * initialCapacity);
    if (!buffer) {
        free(result);
        return NULL;
    }
    result->buffer = buffer;
    result->capacity = initialCapacity;
    result->len = 0;
    return result;
}

void Push(Stack *s, void *value) {
    if (s->len == s->capacity) {
        s->capacity *= 2;
        void *newBuffer = realloc(s->buffer, sizeof(void *) * s->capacity);
        if (!newBuffer) {
            return;
        }
        s->buffer = newBuffer;
    }
    s->buffer[s->len] = value;
    s->len++;
}

void Pop(Stack *s) {
    if (s->len == 0) {
        return;
    }
    free(s->buffer[s->len]);
    s->len--;
}

void *Peek(Stack *s) {
    if (s->len == 0) {
        return NULL;
    }
    return s->buffer[s->len];
}