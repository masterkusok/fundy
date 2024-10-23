#ifndef LR2_10_ERRORS_H
#define LR2_10_ERRORS_H

#include <stdio.h>

typedef enum {
    kS_OK,
    kE_BAD_ALLOC,
} kState;

void logErrors(kState code);

#endif
