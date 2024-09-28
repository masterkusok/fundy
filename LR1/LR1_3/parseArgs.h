#ifndef PARSEARGS_H
#define PARSEARGS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	kS_OK,
	kE_BAD_ALLOCATION,
	kE_INVALID_NUMBER_OF_ARGS,
	kE_UNKNOWN_FLAG,
	kE_INVALID_FLAG,
	kE_INVALID_INPUT,
} kState;

typedef enum {
	kOPT_Q,
	kOPT_M,
	kOPT_T,
} kOpts;

typedef struct {
	kOpts option;
	double* nums;
	int numsLen;
} Request;

Request* ParseArgs(int, char**, kState*);
void LogErrors(kState);

#endif
