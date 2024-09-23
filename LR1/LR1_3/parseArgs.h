#ifndef PARSEARGS_H
#define PARSEARGS_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum {
    kSTATE_OK,
    kSTATE_BAD_ALLOCATION,
    kSTATE_INVALID_NUMBER_OF_ARGS,
    kSTATE_UNKNOWN_FLAG,
    kSTATE_INVALID_FLAG
} kState;

typedef enum {
    kOPT_Q,
    kOPT_M,
    kOPT_T
} kOpts;

typedef struct {
    kOpts option;
    double* nums;
    int numsLen;
} request;

request* parseArgs(int, char**, kState*);
void logErrors(kState);

#endif
