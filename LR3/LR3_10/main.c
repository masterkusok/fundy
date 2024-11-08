#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "parsing.h"

#define DEFAULT_BUF_SIZE 512

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return kE_INVALID_ARG;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        printf("Failed to open input file\n");
        return kE_CANNOT_OPEN_FILE;
    }

    FILE* outputFile = fopen(argv[2], "w");
    if (!outputFile) {
        printf("Failed to open output file\n");
        fclose(inputFile);
        return kE_CANNOT_OPEN_FILE;
    }

    size_t lineLength = DEFAULT_BUF_SIZE;
    char* line = (char*)malloc(lineLength);
    if (!line) {
        printf("Memory allocation failed for line buffer\n");
        fclose(inputFile);
        fclose(outputFile);
        return kE_BAD_ALLOC;
    }

    while (fgets(line, lineLength, inputFile)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0 || strspn(line, " ") == strlen(line)) {
            continue;
        }

        if (!validParantheses(line)) {
            printf("Unbalanced parentheses in expression: %s\n", line);
            continue;
        }

        int index = 0;
        while (line[index] != '\0') {
            Node* root = parseExpression(line, &index);
            if (root) {
                printTree(root, outputFile, 0);
                fprintf(outputFile, "\n");
                freeTree(root);
            } else {
                break;
            }

            while (line[index] == ' ' || line[index] == ',') index++;
        }
    }

    free(line);
    fclose(inputFile);
    fclose(outputFile);
    return kS_OK;
}
