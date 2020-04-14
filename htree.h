#ifndef HTREE_H
#define HTREE_H

#include "byte.h"

struct HTree {
    struct HTree* left;
    struct HTree* right;
    char sumbol;
    uint count;
    char code[22];
};

typedef struct HTree HTree;

HTree* newTree(const char value, const uint count);
HTree* copyTree(HTree const cpyTree);
HTree const* findCode(HTree const* tree, char const symbol);
char treeFindSymbol(HTree* tree, char const* code, uchar ind);
#endif
