#ifndef LR3_5_VECTOR_H
#define LR3_5_VECTOR_H

#include <stdlib.h>
#include <stdbool.h>
#include "student.h"

typedef struct {
    int len;
    int capacity;
    Student **buffer;
} Vector;

Vector *CreateVector(int);

bool VectorPush(Vector *, Student *);

void DestroyVector(Vector *);

#endif
