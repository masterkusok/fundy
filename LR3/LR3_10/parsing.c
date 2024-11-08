#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "parsing.h"

int validParantheses(const char* expr) {
    int balance = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(') {
            balance++;
        } else if (expr[i] == ')') {
            balance--;
            if (balance < 0) {
                return 0;
            }
        }
    }
    return balance == 0;
}

Node* parseExpression(const char* expr, int* index) {
    while (expr[*index] == ' ') (*index)++;
    if (expr[*index] == '\0' || expr[*index] == ')') return NULL;

    if (expr[*index] == '(') {
        (*index)++;
    }

    if (expr[*index] == ' ' || expr[*index] == ',') {
        (*index)++;
        return parseExpression(expr, index);
    }

    Node* node = createNode(expr[*index]);
    if (!node) return NULL;

    (*index)++;
    while (expr[*index] == ' ') (*index)++;

    if (expr[*index] == '(') {
        (*index)++;
        while (expr[*index] != ')' && expr[*index] != '\0') {
            Node* child = parseExpression(expr, index);
            if (child) {
                if (addChild(node, child) != kS_OK) {
                    freeTree(node);
                    return NULL;
                }
            }
            while (expr[*index] == ' ' || expr[*index] == ',') (*index)++;
        }
        if (expr[*index] == ')') (*index)++;
    }

    return node;
}
