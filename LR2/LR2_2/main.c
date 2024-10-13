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

	code = geometric_mean(&result, 3, 40000.0, 600000000.0, 8000000.0);
	if (code != kS_OK) {
		log_errors(code);
		return code;
	}
	printf("geometric mean is - %lf\n", result);

	// test binpow
	long double base = 5.0;
	int exponent = 10;

	printf("binpow: %Lf^%d=%Lf\n", base, exponent, power(base, exponent));
	return 0;
}
