#ifndef HTREE_H
#define HTREE_H

#include "byte.h"

struct HTree {
    struct HTree* left;
    struct HTree* right;
    char sumbol;
    char code[22];
    uint count;
};

typedef struct HTree HTree;

HTree* newTree(const char value, const uint* const count);
HTree* copyTree(HTree const* const cpyTree);
HTree const* findCode(HTree const* const tree, char const symbol);
char treeFindSymbol(HTree* const tree, char const* const code, uchar const ind);
#endif
