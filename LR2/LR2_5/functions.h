#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_BUFF_SIZE 1024

typedef union {
	int8_t i;
	uint8_t u;
	float f;
	double d;
	char bytes[sizeof(double)];
} MemoryDump;

int oversprintf(char*, char*, ...);
void overfprintf(FILE*, char*, ...);

#endif