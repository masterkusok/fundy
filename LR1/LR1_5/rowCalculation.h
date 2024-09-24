#ifndef CALC_H
#define CALC_H

#include <math.h>

#include "states.h"
#include "stdio.h"

kState calculateRow(double, long double (*)(double x, int n), double, long double*);
long double funcA(double, int);
long double funcB(double, int);
long double funcC(double, int);
long double funcD(double, int);

#endif