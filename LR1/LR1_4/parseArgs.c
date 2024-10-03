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

bool pathEquals(char* path1, char* path2) {
	char *p1 = path1, *p2 = path2;
	while (p1 || p2) {
		if (*p1 != *p2) {
			return false;
		}
		if (*p1 == '\0' || *p2 == '\0') {
			return *p1 == '\0' && *p2 == '\0';
		}
		p1++;
		p2++;
	}
	return true;
}

char* getFileName(char* path) {
	char buffer[99];
	int curLen = 0;
	for (char* i = path; *i; i++) {
		if (*i == '\0') {
			break;
		}
		if (*i == '/' || *i == '\\') {
			curLen = 0;
			continue;
		}
		buffer[curLen] = *i;
		curLen++;
	}
	char* output = malloc((curLen + 1) * sizeof(char));
	for (int i = 0; i < curLen; i++) {
		output[i] = buffer[i];
	}
	output[curLen] = '\0';
	return output;
}

request* parseArgs(int argc, char** args) {
	request* r = malloc(sizeof(request));
	if (r == NULL) {
		return r;
	}
	if (argc < 3) {
		r->state = kE_INVALID_NUMBER_OF_ARGS;
		return r;
	}
	if (argc > 4) {
		r->state = kE_INVALID_NUMBER_OF_ARGS;
		return r;
	}
	char* flag = args[1];
	if (flag[0] != '/' && flag[0] != '-') {
		r->state = kE_INVALID_FLAG;
		return r;
	}
	bool providedOutput = false;

	r->option = -1;
	for (int i = 1; i < strlen(flag); i++) {
		switch (flag[i]) {
			case 'd': {
				r->option = kOPT_D;
				break;
			}
			case 'i': {
				r->option = kOPT_I;
				break;
			}
			case 's': {
				r->option = kOPT_S;
				break;
			}
			case 'a': {
				r->option = kOPT_A;
				break;
			}
			case 'n': {
				providedOutput = true;
				break;
			}
			default: {
				r->state = kE_UNKNOWN_FLAG;
				return r;
			}
		}
	}
	if (providedOutput && argc != 4) {
		r->state = kE_INVALID_NUMBER_OF_ARGS;
		return r;
	}
	if (!providedOutput && argc != 3) {
		r->state = kE_INVALID_NUMBER_OF_ARGS;
		return r;
	}

	char* inputFile = args[2];

	if (!fileExists(inputFile)) {
		r->state = kE_FILE_NOT_EXIST;
		return r;
	}
	r->inputFile = inputFile;

	if (providedOutput) {
		r->outputFile = args[3];
		if (pathEquals(r->inputFile, r->outputFile)) {
			r->state = kE_EQUAL_PATHS;
			return r;
		}
	} else {
		char* filename = getFileName(r->inputFile);
		r->outputFile = malloc((5 + strlen(filename)) * sizeof(char));
		strcpy(r->outputFile, "out_");
		strcat(r->outputFile, filename);
	}

	r->state = kS_OK;
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
			printf("Unknown flag was provided\nAvailable flags are:\n-d\n-i\n-s\n-a\n+n for providing output file\n");
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
		case kE_EQUAL_PATHS: {
			printf("Provided equal input and output files\n");
			break;
		}
		default: {
			printf("Unknown error code\n");
			break;
		}
	}
}