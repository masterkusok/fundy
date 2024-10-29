#ifndef LR3_3_VECTOR_H
#define LR3_3_VECTOR_H

#include <stdlib.h>
#include "employee.h"
#include "arguments.h"

typedef struct {
    int len;
    int capacity;
    Employee** buffer;
} Vector;

typedef int (*ComparatorCallback) (const void*, const void*);

Vector* CreateVector(int);
kState VectorPush(Vector*, Employee*);
void FprintVector(Vector*, FILE*);
void SortVector(Vector*, ComparatorCallback);
void DestroyVector(Vector*);

#endif