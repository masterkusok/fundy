#include "normaCalculation.h"

double MaxNorma(const DimensionVector *v, const void *arg) {
    double max = fabs(v->Coordinates[0]);
    for (int i = 1; i < v->N; i++) {
        if (fabs(v->Coordinates[i]) > max) {
            max = fabs(v->Coordinates[i]);
        }
    }
    return max;
}


double SumNorma(const DimensionVector *v, const void *arg) {
    double p = *(double *) arg;
    double sum = 0.0;
    for (int i = 0; i < v->N; i++) {
        sum += pow(fabs(v->Coordinates[i]), p);
    }
    return pow(sum, 1.0 / p);
}

double MatrixNorma(const DimensionVector *v, const void *arg) {
    double **A = (double **) arg;
    double sum = 0.0;
    for (int i = 0; i < v->N; i++) {
        for (int j = 0; j < v->N; j++) {
            sum += v->Coordinates[i] * A[i][j] * v->Coordinates[j];
        }
    }
    return sqrt(sum);
}

