#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "parsing.h"

Node* createNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->data = data;
    node->children = NULL;
    node->childCount = 0;
    return node;
}

int addChild(Node* parent, Node* child) {
    Node** newChildren = (Node**)realloc(parent->children, (parent->childCount + 1) * sizeof(Node*));
    if (!newChildren) {
        return kE_BAD_ALLOC;
    }
    parent->children = newChildren;
    parent->children[parent->childCount++] = child;
    return kS_OK;
}

void printTree(Node* root, FILE* file, int level) {
    if (!root) return;
    for (int i = 0; i < level; i++) {
        fprintf(file, "\t");
    }
    fprintf(file, "%c\n", root->data);
    for (int i = 0; i < root->childCount; i++) {
        printTree(root->children[i], file, level + 1);
    }
}

void freeTree(Node* root) {
    if (!root) return;
    for (int i = 0; i < root->childCount; i++) {
        freeTree(root->children[i]);
    }
    free(root->children);
    free(root);
}
