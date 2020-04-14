#ifndef HTREE_H
#define HTREE_H

typedef unsigned char uchar;
typedef unsigned long long uint;

struct HTree {
    struct HTree* left;
    struct HTree* right;
    char sumbol;
    uint count;
    char code[16];
};

typedef struct HTree HTree;

HTree* newTree(const char value, const uint count);
HTree* copyTree(HTree const cpyTree);

#endif
