#ifndef LR3_2_NORMACALCULATION_H
#define LR3_2_NORMACALCULATION_H

#include <math.h>
#include "dimensionVector.h"

typedef double (*NormaCalculator)(const DimensionVector *, const void *);

double MaxNorma(const DimensionVector *, const void *);

double SumNorma(const DimensionVector *, const void *);

double MatrixNorma(const DimensionVector *, const void *);

#endif
