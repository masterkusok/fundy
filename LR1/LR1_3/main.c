#include <stdio.h>

#include "handers.h"
#include "parseArgs.h"

int main(int argc, char** args) {
    kState code;
    request* r = parseArgs(argc, args, &code);
    if(code != kSTATE_OK) {
        logErrors(code);
        return code;
    }

    void (*handlers[3])(double*) = {
        handlerOptQ,
        handlerOptM,
        handlerOptT
    };

    handlers[r->option](r->nums);
    return 0;
}
