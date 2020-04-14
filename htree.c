#include "vector.h"
#include <malloc.h>
#include <stddef.h>

HTree* newTree(const char value, const uint count)
{
    HTree* tree = malloc(sizeof(HTree));
    tree->left = NULL;
    tree->right = NULL;
    tree->count = count;
    tree->sumbol = value;
    return tree;
}

HTree* copyTree(HTree const cpyTree)
{
    HTree* tree = newTree(cpyTree.sumbol, cpyTree.count);
    tree->left = cpyTree.left;
    tree->right = cpyTree.right;
    return tree;
}

char const* findCode(HTree const* tree, char const symbol)
{
    if (tree->sumbol == symbol)
        return tree->code;
    if (tree->left) {
        char const* temp = findCode(tree->left, symbol);
        if (temp)
            return temp;
    }
    if (tree->right) {
        char const* temp = findCode(tree->right, symbol);
        if (temp)
            return temp;
    }
    return NULL;
}
