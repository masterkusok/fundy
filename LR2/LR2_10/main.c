#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include "errors.h"

// возвращает значение i-й производной в точке(а), n - порядок многочлена
double derivative(int i, double a, int n, const double *coeffs) {
    double result = 0.0;

    for (int j = i; j <= n; j++) {
        double term = coeffs[j];
        for (int k = 0; k < i; k++) {
            term *= (j - k);
        }
        result += term * pow(a, j - i);
    }
    return result;
}

kState decomposePolynomial(double epsilon, double a, double *result, int n, ...) {
    if (!result) return -1;
    va_list args;
    va_start(args, n);

    double *coeffs = (double *) malloc((n + 1) * sizeof(double));
    if (!coeffs) return kE_BAD_ALLOC;

    for (int i = 0; i <= n; i++) {
        coeffs[i] = va_arg(args, double);
    }
    va_end(args);

    double factorial = 1.0;
    for (int i = 0; i <= n; i++) {
        if (i != 0) {
            factorial *= (double) i;
        }
        result[i] = derivative(i, a, n, coeffs) / factorial;
        if (fabs(result[i]) < epsilon) {
            result[i] = 0.0;
        }
    }

    free(coeffs);
    return kS_OK;
}

double countAt(double* coeffs1, double* coeffs2, int n, double x, double a) {
    double result1 = 0.0;
    double result2 = 0.0;
    double x1 = 1.0;
    double x2 = 1.0;
    for(int i = 0; i < n; i++) {
        result1 += x1 * coeffs1[i];
        result2 += x2 * coeffs2[i];
        x1 *= x;
        x2 *= (x - a);
    }
    printf("%d\n%d\n");
}

int main() {
    int n = 2;
    double epsilon = 1e-6;
    double a = 1.0;
    double* result = malloc((n+1) * sizeof(double));
    if(!result) {
        logErrors(kE_BAD_ALLOC);
        return kE_BAD_ALLOC;
    }
    kState code = decomposePolynomial(epsilon, a, result, n, 2.0, 3.0, 4.0);
    if (code != kS_OK) {
        logErrors(code);
        return code;
    }

    for (int i = 0; i <= n; i++) {
        printf("g%d = %f\n", i, result[i]);
    }
    double arr[3] = {2.0, 3.0, 4.0};
    countAt(arr, result, n, 3, a);

    free(result);
    return kS_OK;
}