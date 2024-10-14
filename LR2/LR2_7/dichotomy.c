#include "dichotomy.h"

double solveDichotomy(double a, double b, equatation f, double epsilon, kState* code) {
	if (f(a) * f(b) >= 0.0) {
		*code = kE_INVALID_BOUNDS;
		return 0.0;
	}
	*code = kS_OK;
	double c;
	int n = 0;
	while ((b - a) / 2 > epsilon) {
		if (n > ITERATION_LIMIT) {
			*code = kE_ITERATION_LIMIT;
			return 0.0;
		}
		c = (a + b) / 2;
		if (f(a) * f(c) > 0) {
			a = c;
		} else {
			b = c;
		}
		n++;
	}
	return c;
}

void logErrors(kState code) {
	switch (code) {
		case kE_ITERATION_LIMIT: {
			printf("Iteration limit exceeded. Try to decrease epsilon or change bounds\n");
			return;
		}
		case kE_INVALID_BOUNDS: {
			printf("Invalid bounds: f(a) * f(b) >= 0");
			return;
		}
		default: {
			printf("Unknown error code\n");
			return;
		}
	}
}
