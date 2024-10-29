#include <sys/stat.h>
#include "arguments.h"

bool fileExists(char *path) {
    FILE *input = fopen(path, "r");
    if (!input) {
        return false;
    }
    fclose(input);
    return true;
}

bool sameFile(const char *path1, const char *path2) {
    struct stat stat1, stat2;
    stat(path1, &stat1);
    stat(path2, &stat2);
    if (stat1.st_ino == stat2.st_ino && stat1.st_dev == stat2.st_dev) {
        return true;
    }
    return false;
}

Args *ParseArgs(int argc, char **argv) {
    Args *result = malloc(sizeof(Args));
    if (!result) {
        return result;
    }

    if (argc < 4 || argc > 4) {
        result->State = kE_INVALID_NUMBER_OF_ARGS;
        return result;
    }

    char *flag = argv[1];
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

    result->InputPath = argv[2];
    if (!fileExists(result->InputPath)) {
        result->State = kE_INVALID_PATH;
        return result;
    }
    result->OutputPath = argv[3];
    if (sameFile(result->InputPath, result->OutputPath)) {
        result->State = kE_SAME_IO_PATH;
    }

    return result;
}