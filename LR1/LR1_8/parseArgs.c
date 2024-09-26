#include "parseArgs.h"

bool fileExists(char* path) {
	FILE* file = fopen(path, "r");
	bool exists = file != NULL;
	if (file != NULL) {
		fclose(file);
	}
	return exists;
}

kState ParseArgs(int argc, char** args, char** inputFile, char** outputFile) {
	if (argc != 3) {
		return kE_INVALID_NUMBER_OF_ARGS;
	}
	*inputFile = args[1];
	if (!fileExists(*inputFile)) {
		return kE_FILE_NOT_EXIST;
	}

	*outputFile = args[2];
	return kS_OK;
}

void LogErrors(kState code) {
	printf("Error:\n");
	switch (code) {
		case kE_INVALID_NUMBER_OF_ARGS: {
			printf("Invalid number of args provided\n");
			break;
		}
		case kE_FILE_NOT_EXIST: {
			printf("Specified file does not exist\n");
			break;
		}
		case kE_INVALID_FILE_CONTENT: {
			printf(
				"Invalid file content. File can include:\nDigits 0-9\nUppercase and lowercase english letters a-z\n");
			break;
		}
		default: {
			printf("Unknown error!\n");
			break;
		}
	}
}