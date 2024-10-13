#include "constantCalculation.h"

long double factorial(int n) {
	long double answ = 1.0;
	for (int i = 1; i <= n; i++) {
		answ *= i;
	}
	return answ;
}

long double C(int m, int k) { return factorial(m) / (factorial(k) * factorial(m - k)); }

long double calculateLimit(double fault, long double (*func)(int, long double)) {
	long double prev = func(1.0L, -0.5L);
	long double current = func(2.0L, prev);
	int n = 3;
	while (fabsl(current - prev) >= fault) {
		prev = current;
		current = func(n, prev);
		n++;
	}
	return current;
}

long double limitE(int n, long double prev) { return powl((1.0 + 1.0 / n), n); }

long double limitPi(int n, long double prev) {
	return powl(powl(2, n) * factorial(n), 4) / (n * powl(factorial(2 * n), 2));
}

long double limitLn2(int n, long double prev) { return n * (powl(2, 1.0 / n) - 1); }

long double limitSqrt2(int n, long double prev) { return prev - prev * prev / 2 + 1; }

long double limitGamma(int n, long double prev) {
	double result = 0.0;
	for (int k = 1; k <= n; k++) {
		result += C(n, k) * powl(-1, k) / k * log(factorial(k));
	}
	return result;
}

long double calculateRowE(double fault) {
	long double current = 1.0, prev = 1.0;
	int n = 2;
	current = 2.0;
	while (fabsl(current - prev) > fault) {
		prev = current;
		current += 1.0 / factorial(n);
		n++;
	}
	return current;
}

long double calculateRowPi(double fault) {
	long double current = 4.0, prev = 4.0;
	int n = 3;
	current = prev - 4.0 / 3.0;
	while (fabsl(current - prev) > fault) {
		prev = current;
		current += 4 * powl(-1, n - 1) / (2 * n - 1);
		n++;
	}
	return current;
}

long double calculateRowLn2(double fault) {
	long double current = 1.0, prev = 1.0;
	int n = 3;
	current = prev - 1.0 / 2.0;
	while (fabsl(current - prev) > fault) {
		prev = current;
		current += powl(-1, n - 1) / n;
		n++;
	}
	return current;
}

long double rowSqrt2(int k) { return pow(2, pow(2, -k)); }

long double calculateRowSqrt2(double fault) {
	long double current = rowSqrt2(2), prev = current;
	int n = 4;
	current *= rowSqrt2(3);
	while (fabsl(current - prev) > fault) {
		prev = current;
		current *= rowSqrt2(n);
		n++;
	}
	return current;
}

long double calculateRowGamma(double fault) {
	fault = 0.000000000001;
	long double current = 0;
	long double prev = 0;
	long double k = 2.0L;
	do {
		prev = current;
		long double appender = (1.0L / (powl(floorl(sqrtl(k)), 2.0L)) - 1.0L / k);
		if (appender < 0.0000000000001) {
			prev = 0.0;
		}
		current += appender;
		k += 1.0L;
	} while (fabsl(current - prev) >= fault);

	return current - M_PI * M_PI / 6.0L;
}

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

// cosx + 1 = 0;
long double piEquatation(long double fault) {
	long double currentX = 0.0;
	long double currentF = 2.0;
	do {
		currentF = cosl(currentX) + 1;
		currentX += M_PI / 720.0;
	} while (fabsl(currentF) > fault);
	return currentX;
}

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