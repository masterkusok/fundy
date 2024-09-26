#include "callbacks.h"
#include "parseArgs.h"

int main(int argc, char** args) {
	request* r = parseArgs(argc, args);
	if (r->state != kS_OK) {
		logErrors(r->state);
		return r->state;
	}

	void (*handlers[4])(char*, char*, char*) = {
		HandleOptR,
		HandleOptA,
	};
	handlers[r->option](r->file1, r->file2, r->outputFile);
	return 0;
}
