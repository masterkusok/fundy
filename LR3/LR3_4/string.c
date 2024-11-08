#include "string.h"

size_t strlen(const char *s) {
    size_t count = 0;
    for (char *i = s; *i; i++) {
        count++;
    }
    return count;
}

size_t StringLen(String *s) {
    return strlen(s->buffer);
}

String *NewString(const char *s) {
    String *result = malloc(sizeof(String));
    if (!result) {
        return NULL;
    }
    size_t len = strlen(s);
    char *buffer = malloc(sizeof(char) * (strlen(s) + 1));

    if (!buffer) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        buffer[i] = s[i];
    }
    result->buffer = buffer;
    result->buffer[len] = '\0';
    result->Len = len;
    return result;
}

void DeleteString(String *s) {
    free(s->buffer);
    free(s);
}

int StringComp(String *s1, String *s2) {
    if (s1->Len != s2->Len) {
        return s1->Len < s2->Len;
    }
    for (int i = 0; i < s1->Len; i++) {
        if (s1->buffer[i] == s2->buffer[i]) {
            continue;
        }
        return s1->buffer[i] < s2->buffer[i] ? -1 : 1;
    }
    return 0;
}

bool StringEqual(String *s1, String *s2) {
    return !StringComp(s1, s2);
}

String *CopyString(String *s) {
    return NewString(s->buffer);
}

void CopyStringTo(String *s1, String *s2) {
    char *newBuffer = malloc(sizeof(char) * (s1->Len + 1));
    if (!newBuffer) {
        return;
    }
    DeleteString(s2);
    s2->buffer = newBuffer;
    s2->Len = s1->Len;
    for (int i = 0; i < s1->Len; i++) {
        s2->buffer[i] = s1->buffer[i];
    }
    s2->buffer[s2->Len] = '\0';
}

void ConcatStrings(String *s1, String *s2) {
    char *newBuffer = realloc(s1->buffer, sizeof(char) * (s1->Len + s2->Len + 1));
    if (!newBuffer) {
        return;
    }
    for (int i = s1->Len; i < s1->Len + s2->Len; i++) {
        newBuffer[i] = s2->buffer[i - s1->Len];
    }
    newBuffer[s1->Len + s2->Len] = '\0';
    s1->buffer = newBuffer;
    s1->Len += s2->Len;
}