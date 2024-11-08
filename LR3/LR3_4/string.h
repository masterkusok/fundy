#ifndef LR3_4_STRING_H
#define LR3_4_STRING_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    size_t Len;
    char *buffer;
} String;

size_t StringLen(String *);

String *NewString(const char *);

void DeleteString(String *);

int StringComp(String *, String *);

bool StringEqual(String *, String *);

String *CopyString(String *);

void CopyStringTo(String *, String *);

void ConcatStrings(String *, String *);

#endif