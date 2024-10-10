#include "parseArgs.h"

kState parseInt(char* input, int* output) {
	int result = 0;
	for (char* i = input; *i; i++) {
		if (*i == '\0') {
			break;
		}
		if (*i <= '9' && *i >= '0') {
			result *= 10;
			result += *i - '0';
		} else {
			return kE_INVALID_ARG;
		}
	}
	*output = result;
	return kS_OK;
}

int strLen(char* string) {
	int len = 0;
	for (char* i = string; *i; i++) {
		len++;
	}
	return len;
}

Input* CreateInput(kState code, kOption option, char** strings, int strLen, int seed) {
	Input* input = malloc(sizeof(Input));
	if (!input) {
		return NULL;
	}
	input->strings = strings;
	input->code = code;
	input->opt = option;
	input->stringsLen = strLen;
	input->seed = seed;
	return input;
}

void DestroyInput(Input* input) {
	if (input->strings != NULL) {
		free(input->strings);
	}
	free(input);
}

Input* ParseArgs(int argc, char** argv) {
	if (argc < 2) {
		return CreateInput(kE_INVALID_NUMBER_OF_ARGS, 0, NULL, 0, 0);
	}

	char* flagStr = argv[1];
	if (flagStr[0] != '-') {
		return CreateInput(kE_UNKNOWN_FLAG, 0, NULL, 0, 0);
	}

	kOption opt;
	switch (flagStr[1]) {
		case 'l': {
			opt = kOPT_L;
			break;
		}
		case 'r': {
			opt = kOPT_R;
			break;
		}
		case 'u': {
			opt = kOPT_U;
			break;
		}
		case 'n': {
			opt = kOPT_N;
			break;
		}
		case 'c': {
			char** strings = malloc(sizeof(char*) * (argc - 3));
			for (int i = 0; i < argc - 3; i++) {
				strings[i] = argv[i + 3];
			}
			int seed = 0;
			kState code = parseInt(argv[2], &seed);
			if (code != kS_OK) {
				return CreateInput(code, kOPT_C, NULL, 0, 0);
			}

			return CreateInput(code, kOPT_C, strings, argc - 3, seed);
		}
		default: {
			return CreateInput(kE_UNKNOWN_FLAG, 0, NULL, 0, 0);
		}
	}

	if (argc != 3) {
		return CreateInput(kE_INVALID_NUMBER_OF_ARGS, 0, NULL, 0, 0);
	}

	char** strings = malloc(sizeof(argv[2]));
	strings[0] = argv[2];
	return CreateInput(kS_OK, opt, strings, 1, 0);
}

void LogErrors(kState code) {
	printf("ERROR DURING PARSING ARGUMENTS:\n");
	switch (code) {
		case kE_INVALID_NUMBER_OF_ARGS: {
			printf("INVALID NUMBER OF ARGS\n");
			break;
		}
		case kE_INVALID_ARG: {
			printf("INVALID ARG: INT EXPECTED\n");
			break;
		}
		case kE_UNKNOWN_FLAG: {
			printf("UNKNOWN FLAG\n");
			break;
		}
		case kE_BAD_ALLOCATION: {
			printf("BAD ALLOCATION\n");
			break;
		}
	}
}
