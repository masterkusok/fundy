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

long double factorial(long double n) {
	long double result = 1.0;
	while (n > 1) {
		result *= n;
		n--;
	}
	return result;
}

long double logFactorial(long double n) {
	long double result = 0.0;
	while (n > 1) {
		result += log(n);
		n--;
	}
	return result;
}

long double logDoubleFactorial(long double n) {
	long double result = 0.0;
	while (n > 1) {
		result += log(n);
		n -= 2;
	}
	return result;
}

kState calculateRow(double epsilon, int from, long double (*func)(double x, int n), double x, long double* output) {
	long double sum = 0.0, current = 0.0;
	int n = from;

	do {
		current = func(x, n);
		if (isinf(current)) {
			return kME_TYPE_OVERFLOW;
		}
		sum += current;
		n += 1;
	} while (fabsl(current) > epsilon && n < 170);

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
	long double log1 = 3 * n * log(3);
	long double log2 = 3 * logFactorial(n);
	long double log3 = 2 * n * log(x);
	long double log4 = logFactorial(3 * n);

	long double result = log1 + log2 + log3 - log4;

	return exp(result);
}

long double funcD(double x, int n) {
	long double log1 = logDoubleFactorial(2 * n - 1);
	long double log2 = 2 * n * log(fabs(x));
	long double log3 = logDoubleFactorial(2 * n);
	double result = log1 + log2 - log3;
	if (n % 2 == 0) {
		return exp(result);
	}
	return -exp(result);
}