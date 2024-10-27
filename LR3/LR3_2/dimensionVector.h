#ifndef LR3_2_DIMENSIONVECTOR_H
#define LR3_2_DIMENSIONVECTOR_H

#include <stdarg.h>
#include <stdlib.h>

typedef struct {
    int N;
    double *Coordinates;
} DimensionVector;

void DestroyDimensionVector(DimensionVector *);

DimensionVector *CopyDimensionVector(DimensionVector *);

DimensionVector *NewDimensionVector(int, ...);

#endif