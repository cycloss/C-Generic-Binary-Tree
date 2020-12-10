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

/**
 * @param valueFormatter is a function pointer to a function that takes a void pointer that must be cast into the tree's node's value type, and then formatted into a string for printing in the tree diagram with sprintf. The char pointer parameter should be passed into the sprintf function as its buffer.
 */
void drawTree(binaryNode* root, void (*valueFormatter)(void*, char*));
void inOrderTraverse(binaryNode* rootNode, void (*printer)(void*));
void reverseOrderTraverse(binaryNode* rootNode, void (*printer)(void*));
#endif