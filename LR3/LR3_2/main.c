#include "dimensionVector.h"
#include "states.h"
#include "vector.h"
#include "normaCalculation.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <stdarg.h>

#define EPS 0.0000001

void FreeVectors(Vector **vectors, int count) {
    for (int i = 0; i < count; i++) {
        if (vectors[i]) {
            DestroyVector(vectors[i]);
        }
    }
    free(vectors);
}

Vector **GetMaxNorma(kState *code, int dimension, int numberOfVectors, int numberOfNormas, ...) {
    va_list args;
    va_start(args, numberOfNormas);

    DimensionVector **vectors = malloc(sizeof(DimensionVector *) * numberOfVectors);
    if (!vectors) {
        va_end(args);
        *code = kE_BAD_ALLOCATION;
        return NULL;
    }

    Vector **output = malloc(sizeof(Vector *) * numberOfNormas);
    if (!output) {
        free(vectors);
        va_end(args);
        *code = kE_BAD_ALLOCATION;
        return NULL;
    }

    for (int i = 0; i < numberOfVectors; i++) {
        vectors[i] = va_arg(args, DimensionVector*);
    }

    for (int k = 0; k < numberOfNormas; k++) {
        output[k] = CreateVector(1);
        if (!output[k]) {
            FreeVectors(output, k);
            free(vectors);
            va_end(args);
            *code = kE_BAD_ALLOCATION;
            return NULL;
        }

        NormaCalculator f = va_arg(args, NormaCalculator);
        void *arg = va_arg(args, void*);
        double longestNorma = -DBL_MAX;

        for (int i = 0; i < numberOfVectors; i++) {
            double norma = f(vectors[i], arg);

            if (longestNorma < norma) {
                longestNorma = norma;
                DestroyVector(output[k]);
                output[k] = CreateVector(1);
                VectorPush(output[k], CopyDimensionVector(vectors[i]));
            } else if (fabs(longestNorma - norma) < EPS) {
                VectorPush(output[k], CopyDimensionVector(vectors[i]));
            }
        }
    }
    free(vectors);
    va_end(args);
    *code = kS_OK;
    return output;
}

int main(void) {
    DimensionVector *v1 = NewDimensionVector(3, 1.0, 2.0, 3.0);
    DimensionVector *v2 = NewDimensionVector(3, 15.0, 22.0, 33.0);
    DimensionVector *v3 = NewDimensionVector(3, 1.0, 2.0, 33.0);
    kState code;
    int numberOfNormas = 2;
    int numberOfVectors = 3;
    int p = 1;
    Vector **result = GetMaxNorma(&code, 3, numberOfVectors, numberOfNormas, v1, v2, v3, MaxNorma, NULL, SumNorma, &p);
    if (code != kS_OK) {
        DestroyDimensionVector(v1);
        DestroyDimensionVector(v2);
        DestroyDimensionVector(v3);
        return code;
    }

    for (int i = 0; i < numberOfNormas; i++) {
        printf("Longest vectors of %d-th norma: \n", i);
        for (int j = 0; j < result[i]->len; j++) {
            DimensionVector *v = result[i]->buffer[j];
            for (int k = 0; k < v->N; k++) {
                printf("%lf ", v->Coordinates[k]);
            }
            printf("\n");
        }
    }

    DestroyDimensionVector(v1);
    DestroyDimensionVector(v2);
    DestroyDimensionVector(v3);
    FreeVectors(result, numberOfNormas);

    return 0;
}