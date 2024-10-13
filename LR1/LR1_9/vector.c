#include "vector.h"

Vector* CreateVector(int initialCapacity) {
	Vector* v = malloc(sizeof(Vector));
	v->buffer = malloc(sizeof(int) * initialCapacity);
	v->capacity = initialCapacity;
	v->len = 0;
	return v;
}

void DestroyVector(Vector* v) {
	free(v->buffer);
	free(v);
};

void PrintVector(Vector* v) {
	for (int i = 0; i < v->len; i++) {
		printf("%d ", v->buffer[i]);
	}
	printf("\n");
}

void VectorPush(Vector* v, int value) {
	if (v->len + 1 >= v->capacity) {
		int* newBuffer = malloc(v->capacity * sizeof(int) * 2);
		for (int i = 0; i < v->len; i++) {
			newBuffer[i] = v->buffer[i];
		}

		free(v->buffer);
		v->buffer = newBuffer;
		v->capacity *= 2;
	}
	v->buffer[v->len] = value;
	v->len++;
}

int VectorPop(Vector* v, Iterator* iter) {
	for (int i = iter->index; i + 1 < v->len; i++) {
		v->buffer[i] = v->buffer[i + 1];
	}
	v->len--;
}

Iterator* CreateIterator(Vector* v) {
	Iterator* iter = malloc(sizeof(Iterator));
	iter->v = v;
	iter->index = 0;
	return iter;
}

void DestroyIterator(Iterator* iter) { free(iter); };

bool IterIsLast(Iterator* iter) { return iter->index >= iter->v->len; }

void IterNext(Iterator* iter) {
	if (!IterIsLast(iter)) {
		iter->index++;
	}
}

int IterValue(Iterator* iter) { return iter->v->buffer[iter->index]; }