#ifndef CONSTANTCALCULATION_H
#define CONSTANTCALCULATION_H

#include<math.h>
#include<stdbool.h>
#include <stdio.h>
#include<float.h>

// Limits calculation
long double calculateLimit(double, long double (*)(int, long double));
long double limitE(int, long double);
long double limitPi(int, long double);
long double limitLn2(int, long double);
long double limitSqrt2(int, long double);
long double limitGamma(int, long double);

// Row calculation

long double calculateRowE(double);
long double calculateRowPi(double);
long double calculateRowLn2(double);
long double calculateRowSqrt2(double);
long double calculateRowGamma(double);


// Equatation calculation
long double solveEquatation(double, long double (*) (long double), long double, long double);
long double eEquatation(long double);
long double sqrt2Equatation(long double);
long double ln2Equatation(long double);
long double piEquatation(long double x);
long double gammaEquatation(long double);

#endif