#include "vector.h"

Vector* CreateVector(int initialCapacity, kState* code) {
	*code = kS_OK;
	Vector* v = malloc(sizeof(Vector));
	if (!v) {
		*code = kE_BAD_ALLOCATION;
		return NULL;
	}
	v->buffer = malloc(sizeof(int) * initialCapacity);
	if (!v->buffer) {
		*code = kE_BAD_ALLOCATION;
		return NULL;
	}
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

kState VectorPush(Vector* v, int value) {
	if (v->len + 1 >= v->capacity) {
		int* newBuffer = malloc(v->capacity * sizeof(int) * 2);
		if (!newBuffer) {
			return kE_BAD_ALLOCATION;
		}
		for (int i = 0; i < v->len; i++) {
			newBuffer[i] = v->buffer[i];
		}

		free(v->buffer);
		v->buffer = newBuffer;
		v->capacity *= 2;
	}
	v->buffer[v->len] = value;
	v->len++;
	return kS_OK;
}

int VectorPop(Vector* v, Iterator* iter) {
	for (int i = iter->index; i + 1 < v->len; i++) {
		v->buffer[i] = v->buffer[i + 1];
	}
	v->len--;
}