#ifndef PARSEARGS_H
#define PARSEARGS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "states.h"

typedef enum {
	kOPT_R,
	kOPT_A,
} kOpts;

typedef struct {
	kState state;
	kOpts option;
	char* file1;
	char* file2;
	char* outputFile;
} request;

request* parseArgs(int, char**);
void logErrors(kState);

#endif
