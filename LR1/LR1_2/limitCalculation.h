#ifndef CONSTANTCALCULATION_H
#define CONSTANTCALCULATION_H

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "states.h"

// Limits calculation
kSTATE limitE(double, long double*);
kSTATE limitPi(double, long double*);
kSTATE limitLn2(double, long double*);
kSTATE limitSqrt2(double, long double*);
kSTATE limitGamma(double, long double*);

#endif