#include "functions.h"

void log_errors(kState code) {
	switch (code) {
		case kE_TYPE_OVERFLOW: {
			printf("ERROR: type overflow\n");
			break;
		}
		case kE_NEGATIVE_SQRT: {
			printf("ERROR: cant take root from negative number\n");
			break;
		}
		default: {
			printf("UNKNOWN ERROR CODE");
			break;
		}
	}
}

int main(int argc, char** argv) {
	// test geom mean
	kState code;
	double result;

	code = geometric_mean(&result, 3, 6.0, 8.0, 10.0);
	if (code != kS_OK) {
		log_errors(code);
		return code;
	}
	printf("geometric mean is: %lf\n", result);

	// test binpow
	code = kS_OK;
	long double base = -2.0;
	int exponent = 3;
	long double resultL = power(base, exponent, &code);
	if (code != kS_OK) {
		log_errors(code);
		return code;
	}
	printf("binpow: %Lf^%d=%Lf\n", base, exponent, resultL);
	return 0;
}
