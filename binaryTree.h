#ifndef BINARY_TREE_L
#define BINARY_TREE_L

#include <stdbool.h>

typedef struct binaryNode {
    void* valuep;
    struct binaryNode* leftNode;
    struct binaryNode* rightNode;
} binaryNode;

binaryNode* createBSTNode(void* valuep);
void freeBST(binaryNode* root, bool freeValues);
void drawTree(binaryNode* root);

#endif