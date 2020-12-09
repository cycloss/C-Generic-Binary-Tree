
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

static char* createTreeDiagram(binaryNode* node, char* top, char* root, char* bottom) {
    //for if one of the forks is null
    if (!node) {
        return concatStrsToNew(root, "null\n");
    }

    //for if is a leaf
    if (!node->leftNode && !node->rightNode) {
        char formatted[20];
        sprintf(formatted, "%i\n", *(int*)node->valuep);
        //if top leaf, root will be ┌──, if bottom leaf └──
        char* rootAndVal = concatStrsToNew(root, formatted);
        return rootAndVal;
    }

    char* topNew = concatStrsToNew(top, " ");
    char* rootNew = concatStrsToNew(top, "┌──");
    char* bottomNew = concatStrsToNew(top, "| ");
    free(top);

    char* topNext = createTreeDiagram(node->rightNode, topNew, rootNew, bottomNew);
    free(topNew);
    free(rootNew);
    free(bottomNew);

    char* topAndRoot = concatStrsToNew(topNext, root);
    free(root);
    free(topNext);

    char formatted[20];
    sprintf(formatted, "%i\n", *(int*)node->valuep);
    char* topAndRootAndVal = concatStrsToNew(topAndRoot, formatted);
    free(topAndRoot);

    char* topNew2 = concatStrsToNew(bottom, "| ");
    char* rootNew2 = concatStrsToNew(bottom, "└──");
    char* bottomNew2 = concatStrsToNew(bottom, " ");
    free(bottom);

    char* bottomNext = createTreeDiagram(node->leftNode, topNew2, rootNew2, bottomNew2);
    free(topNew2);
    free(rootNew2);
    free(bottomNew2);

    char* final = concatStrsToNew(topAndRootAndVal, bottomNext);
    free(topAndRootAndVal);
    free(bottomNext);
    return final;
}

void drawTree(binaryNode* rootNode) {
    char* top = calloc(1, sizeof(char));
    char* rt = calloc(1, sizeof(char));
    char* bottom = calloc(1, sizeof(char));

    char* fullTree = createTreeDiagram(rootNode, top, rt, bottom);
    printf("%s\n", fullTree);
    free(fullTree);
}
