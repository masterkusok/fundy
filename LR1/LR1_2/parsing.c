#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>

kSTATE parseDouble(char* input, double* output) {
	kSTATE code = kS_OK;
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
			printf("%c\n", input[index]);
			return kE_INVALID_INPUT;
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
	*output = negativeMult * result;
	return code;
}

kSTATE ParseArgs(int argc, char** args, double* fault) {
	if (argc < 2) {
		return kE_NOT_ENOUGH_ARGS;
	}
	if (argc > 2) {
		return kE_TOO_MANY_ARGS;
	}
	kSTATE code = parseDouble(args[1], fault);
	return code;
}

void LogErrors(kSTATE code) {
	switch (code) {
		case kE_TOO_MANY_ARGS: {
			printf("to many args provided\n");
			break;
		}
		case kE_NOT_ENOUGH_ARGS: {
			printf("not enough args provided\n");
			break;
		}
		case kE_INVALID_INPUT: {
			printf("invalid input, please, enter float\n");
			break;
		}
		case kME_TYPE_OVERFLOW: {
			printf("type overflow, try to decrease epsilon for this calculation\n");
			break;
		}
		default: {
			printf("unknown error code\n");
			break;
		}
	}
}