#include "functions.h"

bool isConvex(int n, ...) {
	va_list args;
	va_start(args, n);
	double prevX = va_arg(args, double), prevY = va_arg(args, double);

	va_end(args);
	return true;
}

// k5 * x^5 + k4 * x^4 + k3 * x^3 + k2*x^2 + k1*x + k0
// x(x(x(x(k5*x+k4) + k3) + k2) + k1) + k0

double calculatePolynom(double x, int n, ...) {
	va_list args;
	va_start(args, n);
	double current = va_arg(args, double);
	for (int i = 0; i <= n; i++) {
		double k = va_arg(args, double);
		current *= x;
		current += k;
	}
	va_end(args);
	return current;
}
