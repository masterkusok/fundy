#ifndef CALC_H
#define CALC_H

#include <math.h>

#include "states.h"
#include "stdio.h"

kState calculateRow(double, int, long double (*)(double, int), double, long double*);
long double funcA(double, int);
long double funcB(double, int);
long double funcC(double, int);
long double funcD(double, int);

#endif