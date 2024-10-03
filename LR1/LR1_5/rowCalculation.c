#include "rowCalculation.h"

long double factorial(long double n) {
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

long double funcA(double x, int n) { return powl(x, n) / factorial(n); }

long double funcB(double x, int n) {
	long double result = powl(x, (int)(2 * n)) / factorial(2 * n);
	if (n % 2 == 0) {
		return result;
	}
	return -result;
}

long double funcC(double x, int n) {
	return powl(3, 3 * n) * powl(factorial(n), 3) * powl(x, 2 * n) / factorial(3 * n);
}
long double funcD(double x, int n) {
	long double result = doubleFactorial(2 * n - 1) * powl(x, 2 * n) / doubleFactorial(2 * n);
	if (n % 2 == 0) {
		return result;
	}
	return -result;
}