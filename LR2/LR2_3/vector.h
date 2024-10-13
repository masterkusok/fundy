#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "states.h"

typedef struct {
	int len;
	int capacity;
	int* buffer;
} Vector;

typedef struct {
	int index;
	Vector* v;
} Iterator;

Vector* CreateVector(int, kState*);
void DestroyVector(Vector*);
kState VectorPush(Vector*, int);

#endif