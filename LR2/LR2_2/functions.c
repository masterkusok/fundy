#include "functions.h"

kState geometric_mean(double* result, int count, ...) {
	va_list args;
	va_start(args, count);
	double product = 1.0;

	for (int i = 0; i < count; i++) {
		double num = va_arg(args, double);
		product *= num;
		if (product > DBL_MAX || product < -DBL_MAX) {
			return kE_TYPE_OVERFLOW;
		}
	}

	va_end(args);
	if (product < 0.0) {
		return kE_NEGATIVE_SQRT;
	}

	*result = pow(product, 1.0 / count);
	return kS_OK;
}

bool overflow(double x) {
	if (fabs(x) > DBL_MAX) {
		return true;
	}
	return false;
}

long double power(long double base, int exp, kState* error) {
	if (exp == 0) {
		return 1.0;
	}

	if (exp < 0) {
		return 1.0 / power(base, -exp, error);
	}

	long double half = power(base, exp / 2, error);

	if (*error) {
		return 0.0;
	}

	if (overflow(half)) {
		*error = kE_TYPE_OVERFLOW;
		return 0.0;
	}

	long double result = half * half;

	if (exp % 2 != 0) {
		if (overflow(result)) {
			*error = kE_TYPE_OVERFLOW;
			return 0.0;
		}
		result *= base;
	}

	return result;
}