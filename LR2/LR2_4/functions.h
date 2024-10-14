#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "states.h"

bool isConvexPolygon(int, ...);
double calculatePolynom(double, int, ...);
bool* findKaprekarNumbers(kState*, int, int, ...);

#endif