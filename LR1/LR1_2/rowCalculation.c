#include "rowCalculation.h"

double rowDeltaE(int n) { return 1.0 / n; }

double rowDeltaPi(int n) { return (3.0 - 2.0 * n) / (2.0 * n - 1.0); }

double rowDeltaLn2(int n) { return -1.0 + 1.0 / (double)n; }

double rowDeltaSqrt2(int n) { return powl(2.0, powl(2.0, -n) - powl(2.0, -n + 1.0)); }

kSTATE calculateRow(double* result, int startN, double startValue, deltaFunc f, double epsilon) {
	int n = startN + 1;
	double currentSum = startValue;
	double prevSum = currentSum;
	double currentElem = startValue;
	double prevElem = startValue;

	do {
		prevElem = currentElem;
		currentElem *= f(n);
		prevSum = currentSum;
		currentSum += currentElem;

		if (currentSum > DBL_MAX || currentSum < -DBL_MAX) {
			return kME_TYPE_OVERFLOW;
		}
		n++;
	} while (fabsl(currentElem) > epsilon && fabsl(currentSum - prevSum) > epsilon);

	*result = currentSum;
	return kS_OK;
}

kSTATE calculateSqrt2Row(double* result, double epsilon) {
	int n = 3;
	double currentMult = powl(2.0, 0.25);
	double prevMult = currentMult;
	double currentElem = currentMult;
	double prevElem = currentMult;

	do {
		prevElem = currentElem;
		currentElem *= rowDeltaSqrt2(n);
		prevMult = currentMult;
		currentMult *= currentElem;

		if (currentMult > DBL_MAX || currentMult < -DBL_MAX) {
			return kME_TYPE_OVERFLOW;
		}
		n++;
	} while (fabsl(currentElem) > epsilon && fabsl(currentMult - prevMult) > epsilon);

	*result = currentMult;
	return kS_OK;
}

long double calculateRowGamma(double epsilon) {
	epsilon = 0.000000000001;
	long double current = 0;
	long double prev = 0;
	long double k = 2.0;
	do {
		prev = current;
		long double appender = (1.0 / (powl(floorl(sqrtl(k)), 2.0)) - 1.0 / k);
		if (appender < 0.0000000000001) {
			prev = 0.0;
		}
		current += appender;
		k += 1.0;
	} while (fabsl(current - prev) >= epsilon);

	return current - M_PI * M_PI / 6.0;
}