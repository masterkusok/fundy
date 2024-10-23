#include "functions.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int romanCharToInt(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

int scanRomanInt(const char *input) {
    int total = 0;
    unsigned long len = strlen(input);

    for (int i = 0; i < len; i++) {
        int current = romanCharToInt(input[i]);
        int next = (i + 1 < len) ? romanCharToInt(input[i + 1]) : 0;

        if (current < next) {
            total -= current;
        } else {
            total += current;
        }
    }
    return total;
}

unsigned int scanFibonacciInt(const char *input) {
    unsigned int prev = 1;
    unsigned int current = 1;
    unsigned int result = 0;
    char *p = input;

    if (*p == '1') {
        result += 1;
    } else if (*p != '0') {
        return result;
    }

    ++p;
    if (*p == '1') {
        result += 1;
    } else if (*p != '0') {
        return result;
    }
    ++p;

    while (*p) {
        if (!*(p + 1)) {
            return result;
        }
        unsigned int temp = prev;
        prev = current;
        current = temp + prev;
        if (*p == '1') {
            result += current;
        } else if (*p != '0') {
            return result;
        }

        p++;
    }

    return 0;
}

int scanBaseInt(const char *input, int base) {
    return strtol(input, NULL, base);
}

int scanBaseIntUpper(const char *input, int base) {
    char upperInput[100];
    for (int i = 0; input[i]; i++) {
        upperInput[i] = toupper(input[i]);
    }
    return scanBaseInt(upperInput, base);
}


int overscanf(char *format, ...) {
    va_list args;
    va_start(args, format);
    char inputBuffer[100];

    for (const char *p = format; *p; p++) {
        if (*p == '%') {
            p++;
            if (*p == 'R' && *(p + 1) == 'o') {
                scanf("%s", inputBuffer);
                int *romanIntPtr = va_arg(args, int *);
                *romanIntPtr = scanRomanInt(inputBuffer);
                p+=2;
            } else if (*p == 'Z' && *(p + 1) == 'r') {
                scanf("%s", inputBuffer);
                unsigned int *fibIntPtr = va_arg(args, unsigned int *);
                *fibIntPtr = scanFibonacciInt(inputBuffer);
                p+=2;
            } else if (*p == 'C' && *(p + 1) == 'v') {
                int base = va_arg(args, int);
                scanf("%s", inputBuffer);
                int *baseIntPtr = va_arg(args, int *);
                *baseIntPtr = scanBaseInt(inputBuffer, base);
                p+=2;
            } else if (*p == 'C' && *(p + 1) == 'V') {
                int base = va_arg(args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }
                scanf("%s", inputBuffer);
                int *baseIntUpperPtr = va_arg(args, int *);
                *baseIntUpperPtr = scanBaseIntUpper(inputBuffer, base);
                p+=2;
            } else {
//                char buffer[100];
//                char *start = p - 1;
//                while (*p && !strchr("diouxXeEfFgGaAcspn%", *p)) {
//                    p++;
//                }
//                if (*p) {
//                    p++;
//                    strncpy(buffer, start, p - start);
//                    buffer[p - start] = '\0';
//                   scanf(buffer, args);
//                }
            }
        } else {
            scanf(format, args);
            break;
        }
    }
    va_end(args);
    return 0;
}
