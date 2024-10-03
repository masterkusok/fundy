#include "parseArgs.h"

double parseDouble(char* input, kState* code) {
	double result = 0;
	int index = 0, len = strlen(input);
	*code = kS_OK;
	while (index < len) {
		if ('0' > input[index] || input[index] > '9') {
			break;
		}
		result *= 10;
		result += input[index] - '0';
		index++;
	}

	if (index == len) {
		return result;
	}

	if (input[index] != '.') {
		*code = kE_INVALID_ARG;
		return 0;
	}

	index++;
	double mult = 0.1;
	while (index < len) {
		if ('0' > input[index] || input[index] > '9') {
			*code = kE_INVALID_ARG;
			return 0;
		}
		result += (input[index] - '0') * mult;
		mult *= 0.1;
		index++;
	}
	return result;
}

kState parseArgs(int argc, char** args, double* epsilon, double* x) {
	if (argc != 3) {
		return kE_INVALID_NUMBER_OF_ARGS;
	}
	kState code = kS_OK;
	*epsilon = parseDouble(args[1], &code);
	if (code != kS_OK) {
		return code;
	}
	*x = parseDouble(args[2], &code);
	if (code != kS_OK) {
		return code;
	}

	return kS_OK;
}

void logErrors(kState state) {
	printf("Error:\n");
	switch (state) {
		case kE_INVALID_NUMBER_OF_ARGS: {
			printf("Invalid number of arguments provided\n");
			break;
		}
		case kME_TYPE_OVERFLOW: {
			printf("Target value is too large for long double, try do decrease epsilon\n");
			break;
		}
		case kE_INVALID_ARG: {
			printf("Invalid arg, float expected\n");
			break;
		}
		default: {
			printf("Unknown error code\n");
			break;
		}
	}
}