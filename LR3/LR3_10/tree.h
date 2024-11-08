#ifndef TREE_H
#define TREE_H

#include <stdio.h>

typedef struct Node {
    char data;
    struct Node **children;
    int childCount;
} Node;

Node *createNode(char);

int addChild(Node *, Node *);

void freeTree(Node *);

void printTree(Node *, FILE *, int);

#endif
