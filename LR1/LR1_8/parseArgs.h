#ifndef PARSE_H
#define PARSE_H

#include <stdbool.h>
#include <stdio.h>

#include "states.h"

kState ParseArgs(int, char**, char**, char**);
void LogErrors(kState);

#endif