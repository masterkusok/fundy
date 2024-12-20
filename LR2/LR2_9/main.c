#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    kS_OK,
    kE_INVALID_ARG,
    kE_BAD_ALLOCATION,
} kState;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void sieveOfEratosthenes(bool *primes, int n, int base) {
    for (int i = 0; i <= n; i++) {
        primes[i] = true;
    }
    primes[0] = primes[1] = false;
    for (int p = 2; p * p <= n; p++) {
        if (primes[p]) {
            for (int i = p * p; i <= n; i += p) {
                primes[i] = false;
            }
        }
    }
}

bool checkFraction(int numerator, int denominator, int base) {
    bool isPrime[37];
    sieveOfEratosthenes(isPrime, 36, base);
    for (int i = 2; i <= denominator; i++) {
        if (denominator % i == 0 && isPrime[i]) {
            if (base % i != 0) {
                return false;
            }
        }
    }
    return true;
}

void doubleToFraction(double value, int *numerator, int *denominator, double tolerance) {
    int denom = 1;
    while(fmod(value, 1.0) != 0.0) {
        value *= 10;
        denom *= 10;
    }
    *numerator = (int) value;
    *denominator = denom;
}

bool *checkFractions(kState *code, int base, int fractionsNum, ...) {
    if (base < 2 || base > 36) {
        *code = kE_INVALID_ARG;
        return NULL;
    }

    bool *result = malloc(sizeof(bool) * fractionsNum);
    if (!result) {
        *code = kE_BAD_ALLOCATION;
        return NULL;
    }

    va_list args;
    va_start(args, fractionsNum);
    for (int i = 0; i < fractionsNum; i++) {
        double fraction = va_arg(args, double);
        int numerator, denominator;
        doubleToFraction(fraction, &numerator, &denominator, 0.001);
        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;
        result[i] = checkFraction(numerator, denominator, base);
    }
    va_end(args);
    return result;
}

int main() {
    kState code = kS_OK;
    int fractionsNum = 3;
    int base = 3;
    bool *result = checkFractions(&code, base, fractionsNum, 0.125, 0.5, 0.023);
    if (code != kS_OK) {
        return code;
    }

    for (int i = 0; i < fractionsNum; i++) {
        printf("%d\n", result[i]);
    }

    free(result);
    return 0;
}
