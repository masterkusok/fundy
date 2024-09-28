#ifndef HANDLERS_H
#define HANDLERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum kOpts {
	kOPT_H,
	kOPT_P,
	kOPT_S,
	kOPT_E,
	kOPT_A,
	kOPT_F,
} kOpts;

typedef enum {
	kS_OK,
	kE_INVALID_FLAG_FORMAT,
	kE_UNKNOWN_FLAG,
	kE_TOO_MANY_ARGS,
	kE_NOT_ENOUGH_ARGS,
	kE_INVALID_INPUT,
} kState;

int ParseOpts(int, char**, kOpts*, int*);
void HandleErrors(int);
void HandleOptH(int);
void HandleOptP(int);
void HandleOptS(int);
void HandleOptE(int);
void HandleOptA(int);
void HandleOptF(int);

#endif
