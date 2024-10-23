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

unsigned long long int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    unsigned long long int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
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

    for (int i = 0; i <= n; i++) {
        result[i] = derivative(i, a, n, coeffs) / (double) factorial(i);
        if (fabs(result[i]) < epsilon) {
            result[i] = 0.0;
        }
    }

    free(coeffs);
    return kS_OK;
}

int main() {
    int n = 2;
    double epsilon = 1e-6;
    double a = 1.0;
    double result[3];

    kState code = decomposePolynomial(epsilon, a, result, n, 2.0, 3.0, 4.0);
    if (code != kS_OK) {
        logErrors(code);
        return code;
    }

    for (int i = 0; i <= n; i++) {
        printf("g%d = %f\n", i, result[i]);
    }

    return 0;
}