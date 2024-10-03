#ifndef PARSING_H
#define PARSING_H

#include <string.h>

#include "states.h"

kSTATE ParseArgs(int, char**, double*);
void LogErrors(kSTATE);

#endif
