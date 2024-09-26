#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int len;
	int capacity;
	int* buffer;
} Vector;

typedef struct {
	int index;
	Vector* v;
} Iterator;

Vector* CreateVector(int);
void VectorPush(Vector*, int);
void PrintVector(Vector* v);
int VectorPop(Vector*, Iterator*);

Iterator* CreateIterator(Vector*);
bool IterIsLast(Iterator*);
void IterNext(Iterator*);
int IterValue(Iterator*);

#endif