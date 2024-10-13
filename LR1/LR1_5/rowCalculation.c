#include "rowCalculation.h"

unsigned long long int factorial(int n) {
	if (n > 20) {
		return 0;
	}
	unsigned long long int result = 1.0;
	while (n > 1) {
		result *= n;
		n--;
	}
	return result;
}

unsigned long long int doubleFactorial(int n) {
	if (n > 33) {
		return 0;
	}
	unsigned long long int result = 1;
	while (n > 1) {
		result *= n;
		n -= 2;
	}
	return result;
}

kState calculateRow(double epsilon, int from, kState (*func)(double, int, long double*), double x,
					long double* output) {
	kState code;
	long double sum = 0.0, current = 0.0;
	int n = from;

	do {
		code = func(x, n, &current);
		if (code != kS_OK) {
			return code;
		}
		if (isinf(current)) {
			return kME_TYPE_OVERFLOW;
		}
		sum += current;
		n += 1;
	} while (fabsl(current) > epsilon && n < 170);

	*output = sum;
	return kS_OK;
}

kState funcA(double x, int n, long double* result) {
	*result = powl(x, n) / factorial(n);
	return kS_OK;
}

kState funcB(double x, int n, long double* result) {
	long long int fact2n = factorial(2 * n);
	if (fact2n < 0) {
		return kME_TYPE_OVERFLOW;
	}
	*result = powl(x, (int)(2 * n)) / factorial(2 * n);
	if (n % 2 != 0) {
		*result *= -1;
	}
	return kS_OK;
}

kState funcC(double x, int n, long double* result) {
	unsigned long long int fact3n = factorial(3 * n);
	if (fact3n <= 0) {
		return kME_TYPE_OVERFLOW;
	}
	*result = powl(3, 3 * n) * powl(factorial(n), 3) * powl(x, 2 * n) / fact3n;
	return kS_OK;
}

kState funcD(double x, int n, long double* result) {
	long long unsigned int df = doubleFactorial(2 * n);
	if (df <= 0) {
		return kME_TYPE_OVERFLOW;
	}
	*result = doubleFactorial(2 * n - 1) * powl(x, 2 * n) / doubleFactorial(2 * n);
	if (n % 2 != 0) {
		*result *= -1;
	}
	return kS_OK;
}