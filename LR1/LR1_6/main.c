#include "integrate.h"
#include "parseArgs.h"

int main(int argc, char** args) {
	double epsilon;
	kState code = ParseArgs(argc, args, &epsilon);
	if (code != kS_OK) {
		LogErrors(code);
		return code;
	}

	double (*integrals[4])(double) = {FunctionA, FunctionB, FunctionC, FunctionD};
	double answer = 0.0;

	for (int i = 0; i < 4; i++) {
		code = Integrate(epsilon, integrals[i], &answer);
		if (code != kS_OK) {
			LogErrors(code);
			continue;
		}
		printf("Integral %c: %lf\n", 'A' + i, answer);
	}
	return 0;
}