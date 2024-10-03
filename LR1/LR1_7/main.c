#include "callbacks.h"
#include "parseArgs.h"

int main(int argc, char** args) {
	request* r = parseArgs(argc, args);
	if (r->state != kS_OK) {
		logErrors(r->state);
		int st = r->state;
		free(r);
		return st;
	}

	void (*handlers[4])(char*, char*, char*) = {
		HandleOptR,
		HandleOptA,
	};
	handlers[r->option](r->file1, r->file2, r->outputFile);
	free(r);
	return 0;
}
