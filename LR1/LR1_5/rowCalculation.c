#include "rowCalculation.h"

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

long double factorial(int n) {
	long double result = 1.0;
	while (n > 1) {
		result *= n;
		n--;
	}
	return result;
}

long double doubleFactorial(int n) {
	long double result = 1.0;
	while (n > 1) {
		result *= (double)n;
		n -= 2;
	}
	return result;
}

kState calculateRow(double epsilon, long double (*func)(double x, int n), double x, long double* output) {
	long double sum = 0.0, current = 0.0;
	int n = 0;
	do {
		current = func(x, n);
		sum += current;
		n += 1;
	} while (fabs(current) > epsilon && n < 170);
	*output = sum;
	return kS_OK;
}

long double funcA(double x, int n) { return binpow(x, n) / factorial(n); }

long double funcB(double x, int n) {
	long double result = binpow(x, (int)(2 * n)) / factorial(2 * n);
	if (n % 2 == 0) {
		return result;
	}
	return -result;
}

long double funcC(double x, int n) {
	return binpow(3, 3 * n) * binpow(factorial(n), 3) * binpow(x, 2 * n) / factorial(3 * n);
}

long double funcD(double x, int n) {
	long double result = doubleFactorial(2 * n - 1) * binpow(x, 2 * n) / doubleFactorial(2 * n);
	if (n % 2 == 0) {
		return result;
	}
	return -result;
}