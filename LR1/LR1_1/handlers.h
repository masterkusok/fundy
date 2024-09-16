#ifndef HANDLERS_H
#define HANDLERS_H

#include <stdlib.h>
#include <stdio.h>

typedef enum kOpts {
    kOPT_H,
    kOPT_P,
    kOPT_S,
    kOPT_E,
    kOPT_A,
    kOPT_F
}kOpts;

typedef enum {
    S_OK,
    E_INVALID_FLAG_FORMAT,
    E_UNKNOWN_FLAG,
    E_TOO_MANY_ARGS,
    E_NOT_ENOUGH_ARGS
} State;


int ParseOpts(int, char**, kOpts*, int*);
void HandleErrors(int);
void HandleOptH(int);
void HandleOptP(int);
void HandleOptS(int);
void HandleOptE(int);
void HandleOptA(int);
void HandleOptF(int);

#endif
