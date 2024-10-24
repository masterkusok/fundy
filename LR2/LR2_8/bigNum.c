#include "bigNum.h"

int charToValue(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return -1;
}

char valueToChar(int value) {
    if (value >= 0 && value <= 9) return '0' + value;
    if (value >= 10 && value <= 35) return 'A' + (value - 10);
    return '?';
}

void PrintBigNumber(BigNumber *bigNumber) {
    for (int i = (int) bigNumber->len - 1; i >= 0; i--) {
        printf("%c", valueToChar(bigNumber->buffer[i]));
    }
    printf("\n");
}

void DestroyBigNumber(BigNumber *bigNumber) {
    if (bigNumber->buffer != NULL) {
        free(bigNumber->buffer);
    }
    free(bigNumber);
}

BigNumber *CreateBigNumber(const char *str, int base) {
    BigNumber *result = malloc(sizeof(BigNumber));
    if (!result) {
        return NULL;
    }

    size_t len = strlen(str);
    result->len = len;
    result->capacity = len + 1;
    result->buffer = calloc(result->capacity, sizeof(uint8_t));
    result->base = base;

    if (!result->buffer) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        int value = charToValue(str[len - i - 1]);
        if (value >= base || value < 0) {
            DestroyBigNumber(result);
            return NULL;
        }
        result->buffer[i] = value;
    }
    return result;
}

kState SumBigNumbers(BigNumber *n1, BigNumber *n2) {
    uint8_t carry = 0;
    for (int i = 0; i < n2->len; i++) {
        int sum = n1->buffer[i] + n2->buffer[i] + carry;
        n1->buffer[i] = sum % n1->base;
        carry = sum / n1->base;
    }

    for (int i = n2->len; i < n1->len; i++) {
        int sum = n1->buffer[i] + carry;
        n1->buffer[i] = sum % n1->base;
        carry = sum / n1->base;
        if (carry == 0) break;
    }

    if (carry > 0) {
        if (n1->len < n1->capacity) {
            n1->buffer[n1->len] = carry;
        } else {
            uint8_t *newBuffer = realloc(n1->buffer, n1->capacity * 3 / 2);
            if (!newBuffer) {
                return kE_BAD_ALLOC;
            }
            n1->buffer = newBuffer;
            n1->capacity = n1->capacity * 3 / 2;
            n1->buffer[n1->len] = carry;
        }
        n1->len++;
    }

    return kS_OK;
}

void SwapBigNumbers(BigNumber *n1, BigNumber *n2) {
    uint8_t *tempBuffer = n1->buffer;
    size_t tempLen = n1->len;
    size_t tempCapacity = n1->capacity;
    int tempBase = n1->base;

    n1->buffer = n2->buffer;
    n1->len = n2->len;
    n1->capacity = n2->capacity;
    n1->base = n2->base;

    n2->buffer = tempBuffer;
    n2->len = tempLen;
    n2->capacity = tempCapacity;
    n2->base = tempBase;
}