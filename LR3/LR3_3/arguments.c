#include "arguments.h"

bool fileExists(char* path) {
    FILE* input = fopen(path, "r");
    if (!input) {
        return false;
    }
    fclose(input);
    return true;
}

Args* ParseArgs(int argc, char** argv) {
    Args* result = malloc(sizeof(Args));
    if (!result) {
        return result;
    }

    if (argc < 3 || argc > 3) {
        result->State = kE_INVALID_NUMBER_OF_ARGS;
        return result;
    }

    char* flag = argv[1];
    if (flag[0] != '-' && flag[0] != '/') {
        result->State = kE_UNKNOWN_FLAG;
        return result;
    }

    if (flag[1] == 'd') {
        result->Option = kOptD;
    } else if (flag[1] == 'a') {
        result->Option = kOptA;
    } else {
        result->State = kE_UNKNOWN_FLAG;
        return result;
    }

    result->Path = argv[2];
    if(!fileExists(result->Path)) {
        result->State = kE_INVALID_PATH;
        return result;
    }
    return result;
}