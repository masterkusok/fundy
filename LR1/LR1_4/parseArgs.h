#ifndef PARSEARGS_H
#define PARSEARGS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef enum {
	kS_OK,
	kE_BAD_ALLOCATION,
	kE_INVALID_NUMBER_OF_ARGS,
	kE_UNKNOWN_FLAG,
	kE_INVALID_FLAG,
	kE_FILE_NOT_EXIST,
	kE_EQUAL_PATHS,
} kState;

typedef enum {
	kOPT_D,
	kOPT_I,
	kOPT_S,
	kOPT_A,
} kOpts;

typedef struct {
	kState state;
	kOpts option;
	char* inputFile;
	char* outputFile;
} request;

request* parseArgs(int, char**);
void destroyRequest(request*);
void logErrors(kState);

#endif
