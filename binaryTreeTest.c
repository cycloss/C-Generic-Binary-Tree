#include "binaryTree.h"
#include <stdio.h>

#define len(x) sizeof(x) / sizeof(x[0])

void intFormatter(void* valuep, char* buffer) {
    sprintf(buffer, "%i\n", *(int*)valuep);
}

void intPrinter(void* valuep) {
    printf("%d\n", *(int*)valuep);
}

int main() {

    int vals[] = { 0, 1, 5, 7, 8, 9, 10 };
    binaryNode* nodes[len(vals)];

    for (int i = 0; i < len(vals); i++) {
        nodes[i] = createBSTNode(&vals[i]);
    }

    binaryNode* root = nodes[3];
    root->leftNode = nodes[1];
    nodes[1]->leftNode = nodes[0];
    nodes[1]->rightNode = nodes[2];
    root->rightNode = nodes[5];
    nodes[5]->leftNode = nodes[4];
    nodes[4]->leftNode = nodes[6];
    drawTree(root, intFormatter);
    inOrderTraverse(root, intPrinter);
    puts("Post order:");
    reverseOrderTraverse(root, intPrinter);
    freeBST(root, false);
}