#ifndef LR3_2_VECTOR_H
#define LR3_2_VECTOR_H

#include "dimensionVector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int len;
    int capacity;
    DimensionVector **buffer;
} Vector;

Vector *CreateVector(int);

void DestroyVector(Vector *);

void VectorPush(Vector *, DimensionVector *);

void VectorPop(Vector *);

#endif
