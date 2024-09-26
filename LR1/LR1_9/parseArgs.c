#include "parseArgs.h"

double parseInt(char* input) {
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

	return result;
}

kState ParseArgs(int argc, char** args, int* a, int* b) {
	if (argc != 3) {
		return kE_INVALID_NUMBER_OF_ARGS;
	}

	*a = parseInt(args[1]);
	*b = parseInt(args[2]);
	if (a >= b) {
		return kE_INVALID_INTERVAL;
	}
	return kS_OK;
}

void LogErrors(kState code) {
	printf("Error during parsing arguments:\n");
	switch (code) {
		case kE_INVALID_NUMBER_OF_ARGS: {
			printf("Invalid number of args\n");
			break;
		}
		default: {
			printf("Unknown error\n");
			break;
		}
	}
}