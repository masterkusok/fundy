#include "functions.h"

void zeckendorf(unsigned int n, char *result) {
    unsigned int fib[50];
    fib[0] = 1;
    fib[1] = 2;
    int count = 2;

    while (fib[count - 1] + fib[count - 2] <= n) {
        fib[count] = fib[count - 1] + fib[count - 2];
        count++;
    }
    result[0] = '\0';
    bool used[50];
    for (int i = count-1; i >= 0; i--) {
        if (n >= fib[i]) {
            n -= fib[i];
            used[i] = true;
        } else {
            used[i] = false;
        }
    }

    for (int i = 0; i < count; i++) {
        strcat(result, used[i] ? "1" : "0");
    }
    strcat(result, "1");
}

void intToRoman(int num, char *result) {
    struct {
        int value;
        const char *symbol;
    } roman[] = {{1000, "M"},
                 {900,  "CM"},
                 {500,  "D"},
                 {400,  "CD"},
                 {100,  "C"},
                 {90,   "XC"},
                 {50,   "L"},
                 {40,   "XL"},
                 {10,   "X"},
                 {9,    "IX"},
                 {5,    "V"},
                 {4,    "IV"},
                 {1,    "I"}};

    result[0] = '\0';
    for (int i = 0; i < 13 && num > 0; i++) {
        while (num >= roman[i].value) {
            strcat(result, roman[i].symbol);
            num -= roman[i].value;
        }
    }
}

int toDecimal(char *strNum, int base, bool upper) {
    int result = 0;
    int multiplier = 1;
    if (*strNum == '-') {
        multiplier = -1;
        strNum++;
    }
    for (char *i = strNum; *i; i++) {
        if (*i == '\0') {
            return result * multiplier;
        }
        result *= base;
        int appender = 0;
        if (*i <= '9' && *i >= '0') {
            appender = *i - '0';
        } else if (upper && *i >= 'A' && *i <= 'Z') {
            appender = *i - 'A' + 10;

        } else if (!upper && *i >= 'a' && *i <= 'z') {
            appender = *i - 'a' + 10;
        } else {
            return 0;
        }
        if (appender + 1 > base) {
            return 0;
        }
        result += appender;
    }
    return result * multiplier;
}

void byteToBinaryString(unsigned char byte, char *output) {
    for (int i = 7; i >= 0; --i) {
        output[7 - i] = (byte & (1 << i)) ? '1' : '0';
    }
    output[8] = ' ';
    output[9] = '\0';
}

void memoryDumpToString(char *bytes, size_t size, char *output) {
    char buffer[10];
    output[0] = '\0';

    for (size_t i = 0; i < size; ++i) {
        byteToBinaryString(bytes[i], buffer);
        strcat(output, buffer);
    }
}

int oversprintf(char *str, char *format, ...) {
    va_list args;
    va_start(args, format);
    char *p = format;
    char buffer[1024];
    int total_chars = 0;

    while (*p) {
        if (*p == '%' && *(p + 1)) {
            p++;
            if (*p == 'R' && *(p + 1) == 'o') {
                p += 2;
                int num = va_arg(args, int);
                char roman[512];
                intToRoman(num, roman);
                total_chars += sprintf(str + total_chars, "%s", roman);

            } else if (*p == 'Z' && *(p + 1) == 'r') {
                unsigned int num = va_arg(args, unsigned int);
                char zeckendorfNum[1024];
                zeckendorf(num, zeckendorfNum);
                total_chars += sprintf(str + total_chars, "%s", zeckendorfNum);
                p += 2;

            } else if (*p == 'C' && *(p + 1) == 'v') {
                p += 2;
                int num = va_arg(args, int);
                int base = va_arg(args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }
                char result[100];
                char *ptr = result + sizeof(result) - 1;
                *ptr = '\0';
                do {
                    int currentDigit = num % base;
                    if (currentDigit < 10) {
                        *--ptr = '0' + currentDigit;
                    } else {
                        *--ptr = 'a' + currentDigit - 10;
                    }
                    num /= base;
                } while (num > 0);
                total_chars += sprintf(str + total_chars, "%s", ptr);
            } else if (*p == 'C' && *(p + 1) == 'V') {
                p += 2;
                int num = va_arg(args, int);
                int base = va_arg(args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }
                char result[100];

                char *ptr = result + sizeof(result) - 1;
                *ptr = '\0';

                do {
                    int currentDigit = num % base;
                    if (currentDigit < 10) {
                        *--ptr = '0' + currentDigit;
                    } else {
                        *--ptr = 'A' + currentDigit - 10;
                    }
                    num /= base;
                } while (num > 0);

                total_chars += sprintf(str + total_chars, "%s", ptr);
            } else if (*p == 't' && *(p + 1) == 'o') {
                p += 2;
                char *arg = va_arg(args, char*);
                int base = va_arg(args, int);
                int decimal = toDecimal(arg, base, false);
                total_chars += sprintf(str + total_chars, "%d", decimal);
            } else if (*p == 'T' && *(p + 1) == 'O') {
                p += 2;
                char *arg = va_arg(args, char*);
                int base = va_arg(args, int);
                int decimal = toDecimal(arg, base, true);
                total_chars += sprintf(str + total_chars, "%d", decimal);
            } else if (*p == 'm' && (*(p + 1) == 'i' || *(p + 1) == 'u' || *(p + 1) == 'd' || *(p+1) == 'f')) {
                p++;
                MemoryDump md;
                if (*p == 'i') {
                    md.i = (int8_t) va_arg(args, int);
                } else if (*p == 'u') {
                    md.u = (uint8_t) va_arg(args, int);
                } else if (*p == 'd') {
                    md.d = va_arg(args, double);
                } else if (*p == 'f') {
                    md.f = (float) va_arg(args, double);
                }
                char output[4];
                memoryDumpToString(md.bytes, 4, output);
                total_chars += sprintf(str + total_chars, "%s", output);
            } else {
                char *start = p - 1;
                while (*p && !strchr("diouxXeEfFgGaAcspn%", *p)) {
                    p++;
                }
                if (*p) {
                    p++;
                    strncpy(buffer, start, p - start);
                    buffer[p - start] = '\0';
                    total_chars += vsprintf(str + total_chars, buffer, args);
                }
            }
        } else {
            str[total_chars++] = *p;
            p++;
        }
    }

    str[total_chars] = '\0';
    va_end(args);
    return total_chars;
}

void overfprintf(FILE *out, char *format, ...) {
    va_list args;
    va_start(args, format);
    char *p = format;
    char buffer[1024];
    int total_chars = 0;
    char str[1024];
    while (*p) {
        if (*p == '%' && *(p + 1)) {
            p++;
            if (*p == 'R' && *(p + 1) == 'o') {
                p += 2;
                int num = va_arg(args, int);
                char roman[100];
                intToRoman(num, roman);
                total_chars += sprintf(str + total_chars, "%s", roman);

            } else if (*p == 'Z' && *(p + 1) == 'r') {
                unsigned int num = va_arg(args, unsigned int);
                char zeckendorfNum[1024];
                zeckendorf(num, zeckendorfNum);
                total_chars += sprintf(str + total_chars, "%s", zeckendorfNum);
                p += 2;

            } else if (*p == 'C' && *(p + 1) == 'v') {
                p += 2;
                int num = va_arg(args, int);
                int base = va_arg(args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }
                char result[100];
                char *ptr = result + sizeof(result) - 1;
                *ptr = '\0';
                do {
                    int currentDigit = num % base;
                    if (currentDigit < 10) {
                        *--ptr = '0' + currentDigit;
                    } else {
                        *--ptr = 'a' + currentDigit - 10;
                    }
                    num /= base;
                } while (num);
                total_chars += sprintf(str + total_chars, "%s", ptr);
            } else if (*p == 'C' && *(p + 1) == 'V') {
                p += 2;
                int num = va_arg(args, int);
                int base = va_arg(args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }
                char result[100];
                char *ptr = result + sizeof(result) - 1;
                *ptr = '\0';

                do {
                    int currentDigit = num % base;
                    if (currentDigit < 10) {
                        *--ptr = '0' + currentDigit;
                    } else {
                        *--ptr = 'A' + currentDigit - 10;
                    }
                    num /= base;
                } while (num);

                total_chars += sprintf(str + total_chars, "%s", ptr);
            } else if (*p == 't' && *(p + 1) == 'o') {
                p += 2;
                char *arg = va_arg(args, char*);
                int base = va_arg(args, int);
                int decimal = toDecimal(arg, base, false);
                total_chars += sprintf(str + total_chars, "%d", decimal);
            } else if (*p == 'T' && *(p + 1) == 'O') {
                p += 2;
                char *arg = va_arg(args, char*);
                int base = va_arg(args, int);
                int decimal = toDecimal(arg, base, true);
                total_chars += sprintf(str + total_chars, "%d", decimal);
            } else if (*p == 'm') {
                p++;
                MemoryDump md;
                if (*p == 'i') {
                    md.i = (int8_t) va_arg(args, int);
                } else if (*p == 'u') {
                    md.u = (uint8_t) va_arg(args, int);
                } else if (*p == 'd') {
                    md.d = va_arg(args, double);
                } else if (*p == 'f') {
                    md.f = (float) va_arg(args, double);
                }
                char output[4];
                memoryDumpToString(md.bytes, 4, output);
                total_chars += sprintf(str + total_chars, "%s", output);
            } else {
                char *start = p - 1;
                while (*p && !strchr("diouxXeEfFgGaAcspn%", *p)) {
                    p++;
                }
                if (*p) {
                    p++;
                    strncpy(buffer, start, p - start);
                    buffer[p - start] = '\0';
                    total_chars += vsprintf(str + total_chars, buffer, args);
                }
            }
        } else {
            str[total_chars++] = *p;
            p++;
        }
    }
    str[total_chars] = '\0';
    va_end(args);
    fprintf(out, "%s", str);
}