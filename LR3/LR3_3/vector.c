#include "vector.h"

Vector* CreateVector(int initialCapacity) {
    Vector* v = malloc(sizeof(Vector));
    if (!v) {
        return NULL;
    }

    v->buffer = malloc(sizeof(Employee*) * initialCapacity);
    if (!v->buffer) {
        free(v);
        return NULL;
    }

    v->capacity = initialCapacity;
    v->len = 0;
    return v;
}

void DestroyVector(Vector* v) {
    for (int i = 0; i < v->len; i++) {
        DestroyEmployee(v->buffer[i]);
    }
    free(v->buffer);
    free(v);
};

void FprintVector(Vector* v, FILE* out) {
    for (int i = 0; i < v->len; i++) {
        fprintf(out, "%lu %s %s %lf\n", v->buffer[i]->ID, v->buffer[i]->Name,
               v->buffer[i]->Surname, v->buffer[i]->Salary);
    }
}

kState VectorPush(Vector* v, Employee* value) {
    if (v->len + 1 >= v->capacity) {
        Employee** newBuffer = malloc(v->capacity * sizeof(Employee*) * 2);
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

void SortVector(Vector* v, ComparatorCallback callback) {
    qsort(v->buffer, v->len, sizeof(Employee*), callback);
}