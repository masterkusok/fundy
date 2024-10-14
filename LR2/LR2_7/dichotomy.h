#ifndef DICHOTOMY_H
#define DICHOTOMY_H

#include <math.h>
#include <stdio.h>

typedef enum {
	kS_OK,
	kE_INVALID_BOUNDS,
	kE_ITERATION_LIMIT,
} kState;

#define ITERATION_LIMIT 10000000

typedef double (*equatation)(double);
double solveDichotomy(double, double, equatation, double, kState*);
void logErrors(kState);

#endif