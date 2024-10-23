#include "errors.h"

void logErrors(kState code) {
    switch (code) {
        case kS_OK: {
            printf("Success!\n");
            break;
        }
        case kE_BAD_ALLOC: {
            printf("BAD ALLOCATION ERROR\n");
            break;
        }
    }
}