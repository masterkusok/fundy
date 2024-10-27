#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct Node {
    char value;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(char value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* buildTree(char **str) {
    if (**str == '\0' || **str == ',' || **str == ')') {
        return NULL;
    }

    while (**str == ' ' || **str == '(') {
        (*str)++;
    }

    Node *node = createNode(**str);
    (*str)++;

    if (**str == '(') {
        (*str)++;
        node->left = buildTree(str);
        if (**str == ',') {
            (*str)++;
        }
        node->right = buildTree(str);
        if (**str == ')') {
            (*str)++;
        }
    }

    return node;
}

void printTree(Node *root, int level, FILE *outputFile) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < level; ++i) {
        fprintf(outputFile, "    ");
    }
    fprintf(outputFile, "%c\n", root->value);

    printTree(root->left, level + 1, outputFile);
    printTree(root->right, level + 1, outputFile);
}

void freeTree(Node *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), inputFile)) {
        char *str = line;
        Node *root = buildTree(&str);
        printTree(root, 0, outputFile);
        fprintf(outputFile, "\n");
        freeTree(root);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
