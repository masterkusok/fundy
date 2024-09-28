#include <stdio.h>

#include "handers.h"
#include "parseArgs.h"

int main(int argc, char** args) {
	kState code;
	Request* r = ParseArgs(argc, args, &code);
	if (code != kS_OK) {
		LogErrors(code);
		return code;
	}

	void (*handlers[3])(double*) = {
		handlerOptQ,
		handlerOptM,
		handlerOptT,
	};

	handlers[r->option](r->nums);
	free(r->nums);
	free(r);
	return 0;
}
