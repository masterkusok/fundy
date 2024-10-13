#ifndef CALC_H
#define CALC_H

#include <float.h>
#include <math.h>

#include "states.h"
#include "stdio.h"

typedef double (*deltaFunc)(double, int);

kState calculateRow(double*, int, double, deltaFunc, double, double);
double funcA(double, int);
double funcB(double, int);
double funcC(double, int);
double funcD(double, int);

#endif