#include <stdio.h>
#include <stdlib.h>

typedef enum {
    kS_OK,
    kE_BAD_ALLOCATION,
    kE_INVALID_ARGS
} kState;

void logErrors(kState code) {
    switch (code) {
        case kS_OK: {
            printf("Success!\n");
            break;
        }
        case kE_BAD_ALLOCATION: {
            printf("ERROR: BAD ALLOCATION\n");
            break;
        }
        case kE_INVALID_ARGS: {
            printf("ERROR: INVALID ARGUMENT");
            break;
        }
        default: {
            printf("UNKNOWN ERROR CODE\n");
            break;
        }
    }
}

char* decimalToBase2r(unsigned int number, unsigned short r, kState* code) {
    if (r > 5 || r < 1) {
        *code = kE_INVALID_ARGS;
        return NULL;
    }
    *code = kS_OK;
    unsigned int base = 1 << r;
    unsigned int mask = base - 1;

    char* result = malloc(sizeof(char) * 65);
    if (!result) {
        *code = kE_BAD_ALLOCATION;
        return NULL;
    }
    int index = 0;
    char* chars = "0123456789abcdefghijklmnopqrstuv";

    while (number > 0) {
        result[index++] = chars[(number & mask)];
        number >>= r;
    }

    result[index] = '\0';
    int left = 0;
    int right = index - 1;
    while(left < right) {
        char temp = result[right];
        result[right] = result[left];
        result[left] = temp;
        left++;
        right--;
    }
    return result;
}

int main() {
    char* result;
    unsigned int number = 63;
    unsigned short r = 3;
    kState code = kS_OK;
    result = decimalToBase2r(number, r, &code);
    if (code != kS_OK) {
        logErrors(code);
        return code;
    }
    printf("%s", result);
    free(result);
    return 0;
}