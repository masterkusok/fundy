#ifndef PARSEARGS_H
#define PARSEARGS_H

#include <stdio.h>
#include <stdlib.h>

#include "states.h"

typedef enum {
	kOPT_L,
	kOPT_R,
	kOPT_U,
	kOPT_N,
	kOPT_C,
} kOption;

typedef struct {
	kState code;
	kOption opt;
	char** strings;
	int stringsLen;
	int seed;
} Input;

Input* CreateInput(kState, kOption, char**, int, int);
void DestroyInput(Input*);
Input* ParseArgs(int, char**);
void LogErrors(kState);

#endif