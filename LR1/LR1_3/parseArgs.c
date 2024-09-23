#include "parseArgs.h"

double parseDouble(char* input) {
    double result = 0;
    int index = 0, len = strlen(input);
    while (index < len) {
        if ('0' > input[index] || input[index] > '9') {
            break;
        }
        result *= 10;
        result += input[index] - '0';
        index++;
    }

    if (index == len) {
        return result;
    }

    if(input[index] != '.') {
        return result;
    }

    index++;
    double mult = 0.1;
    while (index < len) {
        if ('0' > input[index] || input[index] > '9') {
            return result;
        }
        result += (input[index] - '0') * mult;
        mult *= 0.1;
        index++;
    }
    return result;
}

request* parseArgs(int argc, char** args, kState* code) {
    if (argc < 4) {
        *code = kSTATE_INVALID_NUMBER_OF_ARGS;
        return NULL;
    }
    if (argc > 6) {
        *code = kSTATE_INVALID_NUMBER_OF_ARGS;
        return NULL;
    }
    char* flag = args[1];
    if (flag[0] != '/' && flag[0] != '-') {
        *code = kSTATE_INVALID_FLAG;
        return NULL;
    }

    request* r = malloc(sizeof(request));
    if(r == NULL) {
        free(r);
        *code = kSTATE_BAD_ALLOCATION;
        return NULL;
    }

    switch (flag[1]) {
        case 'q': {
            r->option = kOPT_Q;
            r->numsLen = 4;
            break;
        }
        case 'm': {
            r->option = kOPT_M;
            r->numsLen = 2;
            break;
        }
        case 't': {
            r->option = kOPT_T;
            r->numsLen = 4;
            break;
        }
        default: {
            free(r);
            *code = kSTATE_UNKNOWN_FLAG;
            return NULL;
        }
    }

    if (argc != 2 + r->numsLen) {
        free(r);
        *code = kSTATE_INVALID_NUMBER_OF_ARGS;
        return NULL;
    }
    r->nums = malloc(sizeof(double) * r->numsLen);
    if(r->nums == NULL) {
        free(r->nums);
        free(r);
        *code = kSTATE_BAD_ALLOCATION;
        return NULL;
    }
    for(int i = 2; i < 2 + r->numsLen; i++) {
        r->nums[i-2] = parseDouble(args[i]);
    }
    *code = kSTATE_OK;
    return r;
}

void logErrors(kState state) {
    printf("Error:\n");
    switch (state) {
        case kSTATE_BAD_ALLOCATION: {
            printf("Error during memory allocation\n");
            break;
        }
        case kSTATE_INVALID_NUMBER_OF_ARGS: {
            printf("Invalid number of arguments provided\n");
            break;
        }
        case kSTATE_UNKNOWN_FLAG: {
            printf("Unknown flag was provided\nAvailable flags are:\n-q\n-t\n-m\n");
            break;
        }case kSTATE_INVALID_FLAG: {
            printf("Invalid flag format\n");
            break;
        }
        default: {
            printf("Unknown error code\n");
            break;
        }
    }
}