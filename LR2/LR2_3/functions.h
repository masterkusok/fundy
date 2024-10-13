#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdarg.h>
#include <stdio.h>

#include "states.h"
#include "vector.h"

kState findEnterancesInFiles(Vector*, Vector*, Vector*, char*, int, ...);
void logErrors(kState);

#endif