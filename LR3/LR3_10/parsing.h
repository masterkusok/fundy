#ifndef PARSING_H
#define PARSING_H

typedef enum {
    kS_OK,
    kE_BAD_ALLOC,
    kE_INVALID_ARG,
    kE_CANNOT_OPEN_FILE
} ErrorCode;

int validParantheses(const char* expr);
Node* parseExpression(const char* expr, int* index);

#endif
