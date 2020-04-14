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
