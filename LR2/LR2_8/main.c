#include <stdarg.h>
#include <stdio.h>
#include "bigNum.h"
#include "states.h"

kState sumBigNumbers(BigNumber **result, int base, int count, ...) {
    if (base < 2 || base > 36) {
        return kE_INVALID_ARG;
    }

    kState code = kS_OK;
    va_list args;
    va_start(args, count);

    BigNumber *sum = CreateBigNumber("0", base);
    for (int i = 0; i < count; i++) {
        char *numberStr = va_arg(args, char *);
        BigNumber *current = CreateBigNumber(numberStr, base);
        if (current == NULL) {
            DestroyBigNumber(sum);
            return kE_BAD_ALLOC;
        }

        if (sum->len < current->len) {
            SwapBigNumbers(sum, current);
        }

        code = SumBigNumbers(sum, current);
        if (code != kS_OK) {
            DestroyBigNumber(sum);
            DestroyBigNumber(current);
            return code;
        }
        DestroyBigNumber(current);
    }

    va_end(args);
    *result = sum;
    return kS_OK;
}

int main() {
    BigNumber *result;
    kState code = sumBigNumbers(&result, 2, 3, "101", "11", "0");
    if (code != kS_OK) {
        return code;
    }
    PrintBigNumber(result);
    DestroyBigNumber(result);
    return kS_OK;
}