#ifndef CALC_H
#define CALC_H

#include <float.h>
#include <math.h>
#include <stdio.h>

#include "states.h"
#include "stdio.h"

typedef double (*deltaFunc)(int);

kSTATE calculateRow(double*, int, double, deltaFunc, double);
kSTATE calculateSqrt2Row(double*, double);
long double calculateRowGamma(double);
double rowDeltaE(int);
double rowDeltaPi(int);
double rowDeltaLn2(int);

#endif