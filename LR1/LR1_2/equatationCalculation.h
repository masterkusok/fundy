#ifndef EQUATATIONS_H
#define EQUATATIONS_H

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

long double solveEquatation(double, long double (*)(long double), long double, long double);
long double eEquatation(long double);
long double sqrt2Equatation(long double);
long double ln2Equatation(long double);
long double piEquatation(long double);
long double gammaEquatation(long double);

#endif