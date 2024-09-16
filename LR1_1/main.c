#include "handlers.h"

int main(const int argc, char** args) {
    kOpts option;
    int argument;
    int code = ParseOpts(argc, args, &option, &argument);
    if (code != 0) {
        HandleErrors(code);
        return code;
    }

    void (*handlers[6])(int) = {
        HandleOptH,
        HandleOptP,
        HandleOptS,
        HandleOptE,
        HandleOptA,
        HandleOptF,
    };

    handlers[option](argument);
    return 0;
}
