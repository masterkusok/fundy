#include "constantCalculation.h"

double binpow(double base, int exp) {
    double result = 1.0;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

long long int factorial(int n) {
    long long int answ = 1;
    for(int i = 1; i <= n; i++) {
        answ *= i;
    }
    return answ;
}

long double C(int m, int k) {
    return factorial(m) / (factorial(k) * factorial(m - k));
}

long double calculateLimit(double fault, long double (*func)(int, long double)) {
    long double prev = func(1, -0.5); // при n=1 (1 + 1/n)^n
    long double current = func(2, prev); // та же формула при n = 2
    int n = 3;
    while (fabs(current - prev) > fault) {
        prev = current;
        current = func(n, prev);
        n++;
    }
    return current;
}

long double limitE(int n, long double prev) {
    return binpow((1.0 + 1.0/n), n);
}

long double limitPi(int n, long double prev) {
    return binpow(binpow(2, n) * factorial(n), 4) / (n * binpow(factorial(2 * n), 2));
}

long double limitLn2(int n, long double prev) {
    return n * (pow(2, 1.0/n) - 1);
}

long double limitSqrt2(int n, long double prev) {
    return prev * prev / 2 + 1;
}

long double limitGamma(int n, long double prev) {
    double result = 0.0;
    for (int k = 1; k <= n; k++) {
        result += C(n, k) * pow(-1, k) / k * log(factorial(k));
    }
    return result;
}

long double calculateRowE(double fault) {
    long double current = 1.0, prev = 1.0;
    int n = 2;
    current = prev + 1.0/factorial(1);
    while (fabs(current-prev) > fault) {
        prev = current;
        current += 1.0/factorial(n);
        n++;
    }
    return current;
}

long double calculateRowPi(double fault) {
    long double current = 4.0, prev = 4.0;
    int n = 3;
    current = prev - 4.0/3.0;
    while (fabs(current-prev) > fault) {
        prev = current;
        current += 4 * binpow(-1, n-1)/(2*n-1);
        n++;
    }
    return current;
}

long double calculateRowLn2(double fault) {
    long double current = 1.0, prev = 1.0;
    int n = 3;
    current = prev - 1.0/2.0;
    while (fabs(current-prev) > fault) {
        prev = current;
        current += binpow(-1, n-1)/n;
        n++;
    }
    return current;
}

long double rowSqrt2(int k) {
    return pow(2, pow(2, -k));
}

long double calculateRowSqrt2(double fault) {
    long double current = rowSqrt2(2), prev = current;
    int n = 4;
    current *= rowSqrt2(3);
    while (fabs(current-prev) > fault) {
        prev = current;
        current *= rowSqrt2(n);
        n++;
    }
    return current;
}
