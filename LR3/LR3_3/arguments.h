#ifndef LR3_3_ARGUMENTS_H
#define LR3_3_ARGUMENTS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    kOptA,
    kOptD
} kOption;

typedef enum {
    kS_OK,
    kE_BAD_ALLOCATION,
    kE_INVALID_NUMBER_OF_ARGS,
    kE_UNKNOWN_FLAG,
    kE_INVALID_PATH,
    kE_SAME_IO_PATH,
    kE_CANNOT_OPEN_FILE,
    KE_VALIDATION_ERROR,
    kE_PARSING_ERROR,
} kState;

typedef struct {
    kState State;
    kOption Option;
    char *InputPath;
    char *OutputPath;
} Args;

Args *ParseArgs(int, char **);

#endif
