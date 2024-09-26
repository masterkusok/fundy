#include "callbacks.h"
#include "parseArgs.h"

int main(int argc, char** args) {
	char* inputFile;
	char* outputFile;
	kState code = ParseArgs(argc, args, &inputFile, &outputFile);
	if (code != kS_OK) {
		LogErrors(code);
		return code;
	}
	code = Handle(inputFile, outputFile);
	if (code != kS_OK) {
		LogErrors(code);
		return code;
	}
	printf("Success!\n");
	return 0;
}