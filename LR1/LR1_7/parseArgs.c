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

bool fileExists(char* path) {
	FILE* file = fopen(path, "r");
	bool exists = file != NULL;
	if (file != NULL) {
		fclose(file);
	}
	return exists;
}

request* parseArgs(int argc, char** args) {
	request* r = malloc(sizeof(request));
	if (r == NULL) {
		return r;
	}
	if (argc > 5 || argc < 4) {
		r->state = kE_INVALID_NUMBER_OF_ARGS;
		return r;
	}

	char* flag = args[1];
	if (flag[0] != '-' && flag[0] != '/') {
		r->state = kE_INVALID_FLAG;
		return r;
	}

	switch (flag[1]) {
		case 'r': {
			if (argc != 5) {
				r->state = kE_INVALID_NUMBER_OF_ARGS;
				return r;
			}
			r->option = kOPT_R;
			break;
		}
		case 'a': {
			if (argc != 4) {
				r->state = kE_INVALID_NUMBER_OF_ARGS;
				return r;
			}
			r->option = kOPT_A;
			break;
		}
		default: {
			r->state = kE_UNKNOWN_FLAG;
			return r;
		}
	}

	r->file1 = args[2];
	if (!fileExists(r->file1)) {
		r->state = kE_FILE_NOT_EXIST;
		return r;
	}

	if (r->option == kOPT_R) {
		r->file2 = args[3];
		if (!fileExists(r->file2)) {
			r->state = kE_FILE_NOT_EXIST;
			return r;
		}
		r->outputFile = args[4];
	} else {
		r->outputFile = args[3];
	}
	return r;
}

void logErrors(kState state) {
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
		case kE_FILE_NOT_EXIST: {
			printf("Specified file does not exist\n");
			break;
		}
		default: {
			printf("Unknown error code\n");
			break;
		}
	}
}