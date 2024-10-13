#include "rowCalculation.h"

kState calculateRow(double* result, int startN, double startValue, deltaFunc f, double epsilon, double x) {
	int n = startN + 1;
	double currentSum = startValue;
	double prevSum = currentSum;
	double currentElem = startValue;
	double prevElem = startValue;

	do {
		prevElem = currentElem;
		currentElem *= f(x, n);
		prevSum = currentSum;
		currentSum += currentElem;

		if (n > 10000) {
			return kME_TYPE_OVERFLOW;
		}

		if (currentSum > DBL_MAX || currentSum < -DBL_MAX) {
			return kME_TYPE_OVERFLOW;
		}
		n++;
	} while (fabsl(currentElem) > epsilon && fabsl(currentSum - prevSum) > epsilon);

	*result = currentSum;
	return kS_OK;
}

double sqr(double x) { return x * x; }

double funcA(double x, int n) { return x / (double)n; }

double funcB(double x, int n) { return x * x / (4.0 * (double)n * (double)n - 2.0 * (double)n) * (-1); }

double funcC(double x, int n) {
	return 9.0 * (double)n * (double)n * x * x / (9.0 * (double)n * (double)n - 9.0 * (double)n + 2.0);
}

double funcD(double x, int n) { return (-1.0) * (x * x) * (2.0 * (double)n - 1) / (2.0 * (double)n); }
