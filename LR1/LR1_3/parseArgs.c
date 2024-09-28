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

Request* ParseArgs(int argc, char** args, kState* code) {
	if (argc < 4 || argc > 6) {
		*code = kE_INVALID_NUMBER_OF_ARGS;
		return NULL;
	}

	char* flag = args[1];
	if (flag[0] != '/' && flag[0] != '-') {
		*code = kE_INVALID_FLAG;
		return NULL;
	}

	Request* r = malloc(sizeof(Request));
	if (r == NULL) {
		*code = kE_BAD_ALLOCATION;
		return NULL;
	}

	switch (flag[1]) {
		case 'q': {
			r->option = kOPT_Q;
			r->numsLen = 4;
			break;
		}
		case 'm': {
			r->option = kOPT_M;
			r->numsLen = 2;
			break;
		}
		case 't': {
			r->option = kOPT_T;
			r->numsLen = 4;
			break;
		}
		default: {
			free(r);
			*code = kE_UNKNOWN_FLAG;
			return NULL;
		}
	}

	if (argc != 2 + r->numsLen) {
		free(r);
		*code = kE_INVALID_NUMBER_OF_ARGS;
		return NULL;
	}
	r->nums = malloc(sizeof(double) * r->numsLen);
	if (r->nums == NULL) {
		free(r);
		*code = kE_BAD_ALLOCATION;
		return NULL;
	}

	for (int i = 2; i < 2 + r->numsLen; i++) {
		*code = parseDouble(args[i], &r->nums[i - 2]);
		if (*code != kS_OK) {
			free(r->nums);
			free(r);
			return NULL;
		}
	}
	*code = kS_OK;
	return r;
}

void LogErrors(kState state) {
	printf("Error:\n");
	switch (state) {
		case kE_BAD_ALLOCATION: {
			printf("Error during memory allocation\n");
			break;
		}
		case kE_INVALID_NUMBER_OF_ARGS: {
			printf("Invalid number of arguments provided\n");
			break;
		}
		case kE_UNKNOWN_FLAG: {
			printf("Unknown flag was provided\nAvailable flags are:\n-q\n-t\n-m\n");
			break;
		}
		case kE_INVALID_FLAG: {
			printf("Invalid flag format\n");
			break;
		}
		default: {
			printf("Unknown error code\n");
			break;
		}
	}
}