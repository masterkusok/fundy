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

long double power(long double base, int exponent) {
	if (exponent == 0) return 1;
	if (exponent < 0) return 1 / power(base, -exponent);
	if (exponent % 2 == 0) {
		long double half = power(base, exponent / 2);
		return half * half;
	}
	return base * power(base, exponent - 1);
}