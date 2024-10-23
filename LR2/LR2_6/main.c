#include "functions.h"

int main() {
    // Пример использования overscanf
    unsigned int fibonacciNumber;
    unsigned int romanNumber;
    int num;
    overscanf("%Zr %Ro", &num, &fibonacciNumber, &romanNumber);
    printf("%d", fibonacciNumber);
    return 0;
}