#include "handlers.h"

int factorial(int n) {
    int result = 1;
    while (n > 0) {
        result *= n;
        n--;
    }
    return result;
}

int binpow(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

int ParseOpts(int argc, char** args, kOpts* result, int* optArgument) {
    if(argc < 3) {
        return E_NOT_ENOUGH_ARGS;
    }

    if (argc > 3) {
        return E_TOO_MANY_ARGS;
    }

    *optArgument = atoi(args[2]);
    char* option = args[1];
    if(option[0] != '/' && option[0] != '-') {
        return E_INVALID_FLAG_FORMAT;
    }
    switch (option[1])
    {
        case 'h':
            *result = kOPT_H;
            break;
        case 'p':
            *result = kOPT_P;
            break;
        case 's':
            *result = kOPT_S;
            break;
        case 'e':
            *result = kOPT_E;
            break;
        case 'a':
            *result = kOPT_A;
            break;
        case 'f':
            *result = kOPT_F;
            break;
        default:
            return E_UNKNOWN_FLAG;
    }

    return S_OK;
}

void HandleErrors(int code) {
    switch (code) {
        case E_TOO_MANY_ARGS: {
            printf("to many args provided\n");
            break;
        }
        case E_NOT_ENOUGH_ARGS: {
            printf("not enough args provided\n");
            break;
        }
        case E_INVALID_FLAG_FORMAT: {
            printf("invalid flag format:\nflag should start with \"-\" or \"\\\"");
            break;
        }
        case E_UNKNOWN_FLAG: {
            printf("unknown flag, supported flags are:\n-h -p -s -e -a -f\n");
            break;
        }
        default: {
            printf("unknown error code\n");
            break;
        }
    }
}

void HandleOptH(int arg) {
    if(arg > 100) {
        printf("no numbers found\n");
    }
    for(int i = 0; i < 101; i++) {
        if(arg * i > 100) {
            break;
        }
        printf("%d ", arg * i);
    }
}

void HandleOptP(int arg) {
    for(int i = 2; i < arg; i++) {
        if(arg % i == 0) {
            printf("number is composite\n");
            return;
        }
    }
    printf("number is prime\n");
}

void HandleOptS(int arg) {
    char result[99];
    int len = 0;
    while(arg > 0) {
        int digit = arg % 16;
        if (digit < 10) {
            result[len] = '0' + digit;
        } else {
            result[len] = 'A' + digit - 10;
        }
        arg /= 16;
        len++;
    }

    for(int i = 1; i <= len; i++) {
        printf("%c ", result[len-i]);
    }
}

void HandleOptE(int arg) {
    if (arg > 10) {
        printf("argument exceeded the limit\n");
    }

    for (int base = 1; base <= 10; ++base) {
        printf("base %d: ", base);
        for (int exp = 1; exp <= arg; ++exp) {
            printf("%d^%d = %d\t", base, exp, binpow(base, exp));
        }
        printf("\n");
    }
}

void HandleOptA(int arg) {
    int s = (1+arg) * arg / 2;
    printf("%d\n", s);
}

void HandleOptF(int arg) {
    if (arg < 0) {
        printf("invalid argument\n");
    }
    printf("%d\n", factorial(arg));
}
