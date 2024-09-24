#include "parseArgs.h"
#include "rowCalculation.h"

int main(int argc, char** args) {
	double epsilon = 0.0;
	double x = 0.0;
	kState code = parseArgs(argc, args, &epsilon, &x);
	if (code != kS_OK) {
		logErrors(code);
		return code;
	}
	long double result = 0.0;
	long double (*callbacks[4])(double x, int n) = {funcA, funcB, funcC, funcD};

	printf("Counting Rows, epsilon=%lf, x=%lf\n", epsilon, x);
	for (int i = 0; i < 4; i++) {
		code = calculateRow(epsilon, callbacks[i], x, &result);
		if (code != kS_OK) {
			printf("Error during calculating %c row:\n", 'A' + i);
			logErrors(code);
			continue;
		}
		printf("function %c: %Lf\n", 'A' + i, result);
	}
	return 0;
}