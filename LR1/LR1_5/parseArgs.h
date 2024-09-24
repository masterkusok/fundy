#ifndef PARSEARGS_H
#define PARSEARGS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "states.h"

kState parseArgs(int, char**, double*, double*);
void logErrors(kState);

#endif
