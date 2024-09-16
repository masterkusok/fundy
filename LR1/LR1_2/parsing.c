#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>

kSTATE parseArgs(int argc, char** args, double* fault) {
    if (argc < 3) {
        return kE_NOT_ENOUGH_ARGS;
    }
    if (argc > 3) {
        return kE_TOO_MANY_ARGS;
    }
    char* flag = args[1];
    if (flag[0] != '-' && flag[0] != '/') {
        return kE_INVALID_FLAG;
    }
    if(flag[1] != 'f') {
        return kE_INVALID_FLAG;
    }
    *fault = atof(args[2]);
    return kS_OK;
}
