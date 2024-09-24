#include "parseArgs.h"

double parseDouble(char* input) {
	double result = 0;
	int index = 0, len = strlen(input);
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
		return result;
	}

	index++;
	double mult = 0.1;
	while (index < len) {
		if ('0' > input[index] || input[index] > '9') {
			return result;
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

	*epsilon = parseDouble(args[1]);
	*x = parseDouble(args[2]);

	return kS_OK;
}

void logErrors(kState state) {
	printf("Error:\n");
	switch (state) {
		case kE_INVALID_NUMBER_OF_ARGS: {
			printf("Invalid number of arguments provided\n");
			break;
		}
		default: {
			printf("Unknown error code\n");
			break;
		}
	}
}