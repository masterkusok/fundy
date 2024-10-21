#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "states.h"

bool isConvexPolygon(int, ...);
kState calculatePolynom(double*, double, int, ...);
bool* findKaprekarNumbers(kState*, int, int, ...);

#endif