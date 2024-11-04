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

int bitwiseIncrement(int n) {
    unsigned int mask = 1;
    while (n & mask) {
        n = n ^ mask;
        mask <<= 1;
    }
    n = n ^ mask;
    return n;
}

int bitwiseDecrement(int n) {
    unsigned int mask = 1;
    while (!(n & mask)) {
        n = n ^ mask;
        mask <<= 1;
    }
    n = n ^ mask;
    return n;
}

char* decimalToBase2r(int number, unsigned short r, kState* code) {
    if (r > 5 || r < 1) {
        *code = kE_INVALID_ARGS;
        return NULL;
    }

    *code = kS_OK;
    unsigned int base = 1 << r;
    unsigned int mask = bitwiseDecrement(base);

    char* result = malloc(sizeof(char) * 65);
    if (!result) {
        *code = kE_BAD_ALLOCATION;
        return NULL;
    }

    unsigned int index = 0;
    char* chars = "0123456789abcdefghijklmnopqrstuv";

    unsigned int absNumber;
    if (number < 0) {
        absNumber = bitwiseIncrement(~number);
        result[index] = '-';
        index = bitwiseIncrement(index);
    } else {
        absNumber = number;
    }

    while (absNumber > 0) {
        result[index] = chars[(absNumber & mask)];
        index = bitwiseIncrement(index);
        absNumber >>= r;
    }

    if (index == 0 || (number == 0 && index == 1)) {
        result[index] = '0';
        index = bitwiseIncrement(index);
    }

    result[index] = '\0';

    int left = (number < 0) ? 1 : 0;
    int right = bitwiseDecrement(index);
    while (left < right) {
        char temp = result[right];
        result[right] = result[left];
        result[left] = temp;
        left = bitwiseIncrement(left);
        right = bitwiseDecrement(right);
    }

    return result;
}


int main() {
    char* result;
    unsigned int number = 63;
    unsigned short r = 1;
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