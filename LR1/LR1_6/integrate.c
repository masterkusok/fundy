#include "integrate.h"

double FunctionA(double x) { return log(1 + x) / x; }

double FunctionB(double x) { return exp(-(x * x) / 2); }

double FunctionC(double x) {
	if (x >= 1) {
		return 0.0;
	}
	return -log(1 - x);
}

double FunctionD(double x) { return pow(x, x); }

kState integrateRectangle(int steps, double (*f)(double), double* output) {
	double step = 1.0 / steps;
	double result = 0.0;
	for (int i = 1; i <= steps; i++) {
		double current = f(i * step);
		result += current;
	}
	*output = result * step;
	return kS_OK;
}

kState Integrate(double epsilon, double (*f)(double), double* output) {
	int steps = 10;
	kState state;
	double current = 0.0, prev = 0.0;
	do {
		prev = current;
		state = integrateRectangle(steps, f, &current);
		if (state != kS_OK) {
			return state;
		}
		steps *= 2;
	} while (fabs(current - prev) > epsilon);
	*output = current;
	return kS_OK;
}