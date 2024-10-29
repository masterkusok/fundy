#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10
#define MAX_LINE_LENGTH 256

// Structure to define a node in the tree
typedef struct Node {
    char label;
    struct Node *children[MAX_CHILDREN];
    int childCount;
} Node;

// Function to create a new node
Node *createNode(char label) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->label = label;
    node->childCount = 0;
    return node;
}

// Function to output the tree structure recursively
void printTree(Node *root, int level, FILE *outputFile) {
    if (root == NULL) return;

    // Print indentation based on level
    for (int i = 0; i < level; i++) fprintf(outputFile, "  ");
    fprintf(outputFile, "%c\n", root->label);

    // Recursively print all children
    for (int i = 0; i < root->childCount; i++) {
        printTree(root->children[i], level + 1, outputFile);
    }
}

// Recursive function to parse the expression and build the tree
Node *parseExpression(char **expr) {
    if (**expr == '\0') return NULL;

    // Create a new node for the current label
    Node *node = createNode(**expr);
    (*expr)++;  // Move to the next character

    // Process children if there is an open parenthesis
    if (**expr == '(') {
        (*expr)++;  // Skip '('
        while (expr != ')' && expr != '\0') {
            if (**expr == ',') {
                (*expr)++;  // Skip commas
            }
            Node *child = parseExpression(expr);
            if (child != NULL) {
                node->children[node->childCount++] = child;
            }
        }
        (*expr)++;  // Skip ')'
    }
    return node;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        perror("Failed to open output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), inputFile)) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';
        char *expr = line;
        Node *root = parseExpression(&expr);
        printTree(root, 0, outputFile);
        fprintf(outputFile, "\n");  // Separate trees for readability

        // Free the tree (optional)
        // Use a recursive function to free memory for each node
    }

    fclose(inputFile);
    fclose(outputFile);
    return EXIT_SUCCESS;
}