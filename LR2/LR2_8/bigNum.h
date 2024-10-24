#ifndef LR2_8_BIGNUM_H
#define LR2_8_BIGNUM_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "states.h"
#include "string.h"

typedef struct {
    int base;
    size_t len;
    size_t capacity;
    uint8_t *buffer;
} BigNumber;

void PrintBigNumber(BigNumber *);

BigNumber *CreateBigNumber(const char *, int);

void DestroyBigNumber(BigNumber *bigNumber);

kState SumBigNumbers(BigNumber *, BigNumber *);

void SwapBigNumbers(BigNumber *, BigNumber *);

#endif
