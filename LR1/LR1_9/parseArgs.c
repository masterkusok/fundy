#include "parseArgs.h"

int parseInt(char* input, kState* code) {
	int result = 0;
	for (char* i = input; *i; i++) {
		if (*i == '\0') {
			break;
		}
		result *= 10;
		if (*i <= '9' && *i >= '0') {
			result += *i - '0';
		} else {
			*code = kE_INVALID_ARG;
			return 0;
		}
	}
	*code = kS_OK;
	return result;
}

kState ParseArgs(int argc, char** args, int* a, int* b) {
	if (argc != 3) {
		return kE_INVALID_NUMBER_OF_ARGS;
	}
	kState code = kS_OK;

	*a = parseInt(args[1], &code);

	if (code != kS_OK) {
		return code;
	}
	*b = parseInt(args[2], &code);

	if (code != kS_OK) {
		return code;
	}

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
		case kE_INVALID_INTERVAL: {
			printf("You entered invalid interval: a should be less than b\n");
			break;
		}
		case kE_INVALID_ARG: {
			printf("Invalid arg: int expected\n");
			break;
		}
		default: {
			printf("Unknown error\n");
			break;
		}
	}
}