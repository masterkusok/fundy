#include "parseArgs.h"

kState parseDouble(char* input, double* output) {
	kState code = kS_OK;
	double result = 0;
	int index = 0, len = strlen(input);
	int negativeMult = 1;
	if (len == 0) {
		*output = 0;
		return code;
	}

	while (index < len) {
		if (result <= 0.00000001 && input[index] == '-') {
			negativeMult *= -1;
			index++;
			continue;
		}
		if (input[index] == '.') {
			break;
		}
		if ('0' > input[index] || input[index] > '9') {
			return kE_INVALID_INPUT;
		}
		result *= 10;
		result += input[index] - '0';
		index++;
	}
	if (input[index] != '.' || index == len) {
		*output = result;
		return code;
	}

	index++;
	double mult = 0.1;
	while (index < len) {
		if ('0' > input[index] || input[index] > '9') {
			break;
		}
		result += (input[index] - '0') * mult;
		mult *= 0.1;
		index++;
	}
	*output = negativeMult * result;
	return code;
}

kState ParseArgs(int argc, char** args, double* epsilon) {
	if (argc != 2) {
		return kE_INVALID_NUMBER_OF_ARGS;
	}

	kState code = parseDouble(args[1], epsilon);
	return code;
}

void LogErrors(kState state) {
	printf("Error:\n");
	switch (state) {
		case kE_INVALID_NUMBER_OF_ARGS: {
			printf("Invalid number of arguments provided\n");
			break;
		}
		case kE_INVALID_INPUT: {
			printf("Invalid input, please, enter valid float\n");
			break;
		}
		default: {
			printf("Unknown error code\n");
			break;
		}
	}
}