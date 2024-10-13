#include "functions.h"

kState findEnterancesInFile(char* substring, char* path, Vector* lines, Vector* chars, Vector* fileIds, int fileId) {
	FILE* fd = fopen(path, "r");
	if (!fd) {
		return kE_CANT_OPEN_FILE;
	}
	kState code;
	int currentLine = 1;
	int currentChar = 1;
	int currentLen = 0;
	int start = 0;
	char currentFile = fgetc(fd);
	char* currentSubstr = substring;

	while (currentFile != EOF) {
		if (currentFile != *currentSubstr) {
			if (*currentSubstr == '\0') {
				code = VectorPush(lines, currentLine);
				if (code != kS_OK) {
					return code;
				}
				code = VectorPush(chars, currentChar);
				if (code != kS_OK) {
					return code;
				}

				code = VectorPush(fileIds, fileId);
				if (code != kS_OK) {
					return code;
				}
			}

			currentSubstr = substring;
			start++;
			fseek(fd, start, SEEK_SET);
			currentFile = fgetc(fd);
			currentChar++;
			if (currentFile == '\n') {
				currentLine++;
				currentChar = 0;
			}
			currentLen = 0;
			continue;
		}

		currentFile = fgetc(fd);
		currentSubstr++;
		currentLen++;
	}

	if (*currentSubstr == '\0') {
		code = VectorPush(lines, currentLine);
		if (code != kS_OK) {
			return code;
		}
		code = VectorPush(chars, currentChar);
		if (code != kS_OK) {
			return code;
		}

		code = VectorPush(fileIds, fileId);
		if (code != kS_OK) {
			return code;
		}
	}
	fclose(fd);
	return kS_OK;
}

kState findEnterancesInFiles(Vector* lines, Vector* chars, Vector* fileIds, char* substring, int count, ...) {
	kState code;
	va_list args;
	va_start(args, count);

	for (int i = 0; i < count; i++) {
		char* path = va_arg(args, char*);
		code = findEnterancesInFile(substring, path, lines, chars, fileIds, i);
		if (code != kS_OK) {
			va_end(args);
			return code;
		}
	}
	va_end(args);
	return code;
}

void logErrors(kState code) {
	switch (code) {
		case kE_BAD_ALLOCATION: {
			printf("ERROR: BAD ALLOCATION\n");
			break;
		}
		case kE_CANT_OPEN_FILE: {
			printf("ERROR: CANT OPEN SPECIFIED FILE\n");
			break;
		}
		default: {
			printf("UNKNOWN ERROR CODE\n");
			break;
		}
	}
}