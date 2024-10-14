#include "dichotomy.h"

double func1(double x) { return x * x - 9 * x + 14; }  // решения - 2.0 и 7.0

int main() {
	kState code = kS_OK;
	double result = solveDichotomy(4, 15.0, func1, 0.0000001, &code);
	if (code != kS_OK) {
		logErrors(code);
		return code;
	}
	printf("%lf\n", result);
	return 0;
}