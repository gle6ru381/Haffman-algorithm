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

union Byte {
    uchar symbol;
    struct Bit {
        uchar b1 : 1;
        uchar b2 : 1;
        uchar b3 : 1;
        uchar b4 : 1;
        uchar b5 : 1;
        uchar b6 : 1;
        uchar b7 : 1;
        uchar b8 : 1;
    } bit;
};
typedef union Byte Byte;

HTree* newTree(const char value, const uint count);
HTree* copyTree(HTree const cpyTree);
char const* findCode(HTree const* tree, char const symbol);

#endif
