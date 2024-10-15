#include "equatationCalculation.h"

long double solveEquatation(double fault, long double (*func)(long double x), long double a, long double b) {
	long double c;
	while (fabsl(b - a) > fault) {
		c = (a + b) / 2.0;
		long double f_a = func(a);
		long double f_b = func(b);
		long double f_c = func(c);

		if (fabs(f_c) < fault) {
			return c;
		}
		if (f_c * f_a < 0) {
			b = c;
		}
		if (f_c * f_b < 0) {
			a = c;
		}
	}
	return (a + b) / 2.0;
}

// от 0.0001 до 10
long double eEquatation(long double x) { return log(x) - 1.0; }

long double piEquatation(long double x) { return sinl(x); }

// // cosx + 1 = 0;
// long double piEquatation(long double fault) {
// 	long double currentX = 0.0;
// 	long double currentF = 2.0;
// 	// первоначальный шаг в 1 rad;
// 	long double step = M_PI / 360;
// 	do {
// 		currentF = cosl(currentX) + 1;
// 		currentX += step;
// 		if (currentF < 0.0 && step < 0.0 || currentF > 0.0 && step > 0.0) {
// 			step *= -0.5;
// 		}
// 	} while (fabsl(currentF) > fault);
// 	return currentX;
// }
// от 0.0001 до 10
long double ln2Equatation(long double x) { return pow(M_E, x) - 2.0; }

// от 0.0001 до 10
long double sqrt2Equatation(long double x) { return x * x - 2; }

void sieveOfEratosthenes(bool *primes, int n) {
	for (int i = 0; i <= n; i++) {
		primes[i] = true;
	}
	primes[0] = primes[1] = false;
	for (int p = 2; p * p <= n; p++) {
		if (primes[p]) {
			for (int i = p * p; i <= n; i += p) {
				primes[i] = false;
			}
		}
	}
}

long double calculateT(double fault) {
	int x = ceill(10.0L / fault);

	bool *primes = (bool *)malloc((x) * sizeof(bool));
	if (!primes) {
		exit(1);
	}
	sieveOfEratosthenes(primes, x);
	long double product = 1.0;
	for (int p = 2; p <= x; p++) {
		if (primes[p]) {
			product *= (1.0L - 1.0L / (long double)p);
		}
	}
	free(primes);

	return log(x) * product;
}

long double gammaEquatation(long double x) { return exp(-x) - calculateT(0.00001); }