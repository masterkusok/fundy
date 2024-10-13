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
	kState (*callbacks[4])(double, int, long double*) = {funcA, funcB, funcC, funcD};
	int intervalStarts[4] = {0, 0, 0, 1};

	printf("Counting Rows, epsilon=%lf, x=%lf\n", epsilon, x);
	for (int i = 0; i < 4; i++) {
		code = calculateRow(epsilon, intervalStarts[i], callbacks[i], x, &result);
		if (code != kS_OK) {
			printf("Error during calculating %c row:\n", 'A' + i);
			logErrors(code);
			continue;
		}
		printf("function %c: %Lf\n", 'A' + i, result);
	}
	return 0;
}