#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <string.h>

#include "states.h"

kState ParseArgs(int, char**, int*, int*);
void LogErrors(kState);

#endif