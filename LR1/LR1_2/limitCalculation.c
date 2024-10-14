#include "limitCalculation.h"

unsigned long long int factorial(int n) {
	unsigned long long int answ = 1;
	for (int i = 2; i <= n; i++) {
		answ *= i;
	}
	return answ;
}

long double factorialLog(int n) {
	long double answ = 0.0;
	for (int i = 1; i <= n; i++) {
		answ += logl(i);
	}
	return answ;
}

unsigned long long int C(int n, int k) {
	unsigned long long int answ = 1;
	for (int i = 0; i < k; i++) {
		answ *= (n - i);
		answ /= (i + 1);
	}
	return answ;
}

kSTATE limitE(double precision, long double* result) {
	long double prev = 0, e = 1;
	int n = 1;
	while (fabsl(e - prev) > precision) {
		prev = e;
		e = powl(1 + 1.0L / n, n);
		if (e > DBL_MAX || e < -DBL_MAX) {
			return kME_TYPE_OVERFLOW;
		}
		n++;
	}
	*result = e;
	return kS_OK;
}

kSTATE limitPi(double precision, long double* result) {
	long double prev = 4.0, pi = 4.0;
	int n = 1;
	do {
		prev = pi;
		pi *= (16.0L * powl(n + 1.0L, 3) * n) / (powl(2.0L * n + 2.0L, 2.0) * powl(2.0L * n + 1.0L, 2));

		if (pi < -DBL_MAX || pi > DBL_MAX) {
			return kME_TYPE_OVERFLOW;
		}
		n++;
	} while (fabs(pi - prev) > precision);
	*result = pi;
	return kS_OK;
}

kSTATE limitLn2(double precision, long double* result) {
	long double prev = 0, ln = 0;
	int n = 1;
	do {
		prev = ln;
		ln = n * (powl(2.0L, 1.0L / n) - 1.0L);
		n++;
	} while (fabs(ln - prev) > precision);
	*result = ln;
	return kS_OK;
}

kSTATE limitSqrt2(double precision, long double* result) {
	long double x = 0.5, xPrev;
	int n = 1;
	do {
		xPrev = x;
		x = x - (powl(x, 2.0L) - 2.0L) / 2.0L;
		n++;
	} while (fabs(x - xPrev) > precision);

	*result = x;
	return kS_OK;
}

kSTATE limitGamma(double precision, long double* result) {
	long double gamma = 1.0, prev = 0.0;
	int m = 1;

	do {
		long double sum = 0.0L;
		for (int k = 1; k <= m; k++) {
			sum += C(m, k) * (powl(-1.0L, k) / k) * factorialLog(k);
			if (fabsl(sum) > DBL_MAX) {
				return kME_TYPE_OVERFLOW;
			}
		}

		prev = gamma;
		gamma = sum;
		if (gamma > DBL_MAX || gamma < -DBL_MAX) {
			return kME_TYPE_OVERFLOW;
		}

		m++;
	} while (fabs(gamma - prev) > precision && m < 100);
	if (fabsl(gamma) > 1.0) {
		return kME_TYPE_OVERFLOW;
	}
	*result = gamma;
	return kS_OK;
}