#include "parsing.h"
#include "constantCalculation.h"
#include "stdio.h"

int main(int argc, char** args) {
    double fault;
    int code = parseArgs(argc, args, &fault);
    if(code != kS_OK) {
        return code;
    }

    long double answer = calculateRowSqrt2(fault);
    printf("%.12lf", answer);
    return 0;
}
