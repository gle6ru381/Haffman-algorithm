#include "vector.h"
#include <malloc.h>
#include <stddef.h>

HTree* newTree(const char value, const uint* const count)
{
    HTree* tree = calloc(1, sizeof(HTree));
    tree->left = NULL;
    tree->right = NULL;
    tree->count = *count;
    tree->sumbol = value;
    return tree;
}

HTree* copyTree(HTree const* const cpyTree)
{
    HTree* tree = newTree(cpyTree->sumbol, &cpyTree->count);
    tree->left = cpyTree->left;
    tree->right = cpyTree->right;
    return tree;
}

HTree const* findCode(HTree const* const tree, char const symbol)
{
    if (tree->sumbol == symbol)
        return tree;
    if (tree->left) {
        HTree const* temp = findCode(tree->left, symbol);
        if (temp)
            return temp;
    }
    if (tree->right) {
        HTree const* temp = findCode(tree->right, symbol);
        if (temp)
            return temp;
    }
    return NULL;
}

char treeFindSymbol(HTree* const tree, char const* const code, uchar const ind)
{
    if (!strcmp(tree->code, code) && tree->count) {
        tree->count--;
        return tree->sumbol;
    }
    if (code[ind] == '0') {
        if (tree->left) {
            char temp = treeFindSymbol(tree->left, code, ind + 1);
            if (temp)
                return temp;
        }
    }
    if (code[ind] == '1') {
        if (tree->right) {
            char temp = treeFindSymbol(tree->right, code, ind + 1);
            if (temp)
                return temp;
        }
    }
    return 0;
}
