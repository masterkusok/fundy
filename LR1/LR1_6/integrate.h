#ifndef INTEGRATE_H
#define INTEGRATE_H

#include <math.h>
#include <stdio.h>

#include "states.h"

double FunctionA(double);
double FunctionB(double);
double FunctionC(double);
double FunctionD(double);
kState Integrate(double, double (*)(double), double*);
kState integrateRectangle(int steps, double (*f)(double), double* output);

#endif