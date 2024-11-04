#ifndef LR3_4_VECTOR_H
#define LR3_4_VECTOR_H

#include <stdlib.h>
#include "mail.h"

typedef struct {
    int len;
    int capacity;
    Mail **buffer;
} Vector;

Vector *CreateVector(int);

bool VectorPush(Vector *, Mail *);

void DestroyVector(Vector *);

void VectorPop(Vector *, int);

#endif
