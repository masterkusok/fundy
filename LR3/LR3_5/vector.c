#include "vector.h"

Vector *CreateVector(int initialCapacity) {
    Vector *v = malloc(sizeof(Vector));
    if (!v) {
        return NULL;
    }

    v->buffer = malloc(sizeof(Student * ) * initialCapacity);
    if (!v->buffer) {
        free(v);
        return NULL;
    }

    v->capacity = initialCapacity;
    v->len = 0;
    return v;
}

void DestroyVector(Vector *v) {
    for (int i = 0; i < v->len; i++) {
        DestroyStudent(v->buffer[i]);
    }
    free(v->buffer);
    free(v);
}

bool VectorPush(Vector *v, Student *value) {
    if (v->len + 1 >= v->capacity) {
        Student **newBuffer = malloc(v->capacity * sizeof(Student *) * 2);
        if (!newBuffer) {
            return false;
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
    return true;
}