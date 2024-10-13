#include "callbacks.h"
#include "parseArgs.h"

int main(int argc, char** args) {
	request* r = parseArgs(argc, args);
	if (r->state != kS_OK) {
		logErrors(r->state);
		return r->state;
	}

	void (*handlers[4])(char*, char*) = {
		HandleOptD,
		HandleOptI,
		HandleOptS,
		HandleOptA,
	};
	handlers[r->option](r->inputFile, r->outputFile);
	destroyRequest(r);
	return kS_OK;
}
