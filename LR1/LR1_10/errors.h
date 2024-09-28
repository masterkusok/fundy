#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
typedef enum {
	kS_OK,
	kE_INVALID_INPUT,
	kE_INVALID_BASE,
} kState;

void LogErrors(kState);

#endif