#ifndef CONSTANTCALCULATION_H
#define CONSTANTCALCULATION_H

#include<math.h>

// Limits calculation
long double calculateLimit(double, long double (*)(int, long double));
long double limitE(int, long double);
long double limitPi(int, long double);
long double limitLn2(int, long double);
long double limitSqrt2(int, long double);
long double limitGamma(int, long double);

// Row calculation
#include <stdio.h>

long double calculateRowE(double);
long double calculateRowPi(double);
long double calculateRowLn2(double);
long double calculateRowSqrt2(double);
long double calculateRowGamma(double);



// Equatation calculation


#endif