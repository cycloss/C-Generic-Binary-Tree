
#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

binaryNode* createBSTNode(void* valuep) {
    binaryNode* bn = malloc(sizeof(binaryNode));
    if (bn) {
        *bn = (binaryNode) { valuep, NULL, NULL };
        return bn;
    } else {
        return NULL;
    }
}

void freeBST(binaryNode* root, bool freeValues) {
    if (root) {
        freeBST(root->leftNode, freeValues);
        freeBST(root->rightNode, freeValues);
        if (freeValues) {
            free(root->valuep);
        }
        free(root);
    }
}

static char* concatStrsToNew(char* str1, char* str2) {
    char* both = calloc(strlen(str1) + strlen(str2) + 1, sizeof(char));
    //if top leaf, root will be ┌──, if bottom leaf └──
    strcpy(both, str1);
    strcat(both, str2);
    return both;
}

static char* createTreeDiagram(void (*valueFormatter)(void*, char*), binaryNode* node, char* top, char* root, char* bottom) {
    //for if one of the forks is null
    if (!node) {
        return concatStrsToNew(root, "null\n");
    }

    //for if is a leaf
    if (!node->leftNode && !node->rightNode) {
        char buffer[20];
        valueFormatter(node->valuep, buffer);

        //if top leaf, root will be ┌──, if bottom leaf └──
        char* rootAndVal = concatStrsToNew(root, buffer);
        return rootAndVal;
    }

    char* topNew = concatStrsToNew(top, "   ");
    char* rootNew = concatStrsToNew(top, "┌──");
    char* bottomNew = concatStrsToNew(top, "|  ");
    //top should not be freed as top was a previous top new which will be freed after top next has been created below
    //same applies to root and bottom, left in for clarity
    //if they were from the first time the function was entered, don't need to be freed anyway as they weren't dynamically allocated
    // free(top);

    char* topNext = createTreeDiagram(valueFormatter, node->rightNode, topNew, rootNew, bottomNew);
    free(topNew);
    free(rootNew);
    free(bottomNew);

    char* topAndRoot = concatStrsToNew(topNext, root);
    // do not free, see above
    // free(root);
    free(topNext);

    char buffer[20];
    valueFormatter(node->valuep, buffer);
    char* topAndRootAndVal = concatStrsToNew(topAndRoot, buffer);
    free(topAndRoot);

    char* topNew2 = concatStrsToNew(bottom, "|  ");
    char* rootNew2 = concatStrsToNew(bottom, "└──");
    char* bottomNew2 = concatStrsToNew(bottom, "   ");
    // do not free, see above
    // free(bottom);

    char* bottomNext = createTreeDiagram(valueFormatter, node->leftNode, topNew2, rootNew2, bottomNew2);
    free(topNew2);
    free(rootNew2);
    free(bottomNew2);

    char* final = concatStrsToNew(topAndRootAndVal, bottomNext);
    free(topAndRootAndVal);
    free(bottomNext);
    return final;
}

void drawTree(binaryNode* rootNode, void (*valueFormatter)(void*, char*)) {

    char* fullTree = createTreeDiagram(valueFormatter, rootNode, "", "", "");
    printf("%s\n", fullTree);
    free(fullTree);
}

void inOrderTraverse(binaryNode* rootNode, void (*printer)(void*)) {
    if (!rootNode) {
        return;
    }
    inOrderTraverse(rootNode->leftNode, printer);
    printer(rootNode->valuep);
    inOrderTraverse(rootNode->rightNode, printer);
}

void reverseOrderTraverse(binaryNode* rootNode, void (*printer)(void*)) {
    if (!rootNode) {
        return;
    }
    reverseOrderTraverse(rootNode->rightNode, printer);
    printer(rootNode->valuep);
    reverseOrderTraverse(rootNode->leftNode, printer);
}
