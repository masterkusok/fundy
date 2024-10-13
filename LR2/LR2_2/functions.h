#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#include "states.h"

kState geometric_mean(double*, int, ...);
long double power(long double, int, kState*);

#endif