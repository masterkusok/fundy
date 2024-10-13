#ifndef CALC_H
#define CALC_H

#include <math.h>

#include "states.h"
#include "stdio.h"

unsigned long long int doubleFactorial(int n);
unsigned long long int factorial(int n);
kState calculateRow(double, int, kState (*)(double, int, long double*), double, long double*);
kState funcA(double, int, long double*);
kState funcB(double, int, long double*);
kState funcC(double, int, long double*);
kState funcD(double, int, long double*);

#endif