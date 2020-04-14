#ifndef BYTE_H
#define BYTE_H
#include <stdio.h>

typedef unsigned char uchar;
typedef unsigned long long uint;

struct Byte {
    uchar bit;
    uchar size;
};
typedef struct Byte Byte;

Byte* byte_init();
void setBit(Byte* byte, char bit);
char* toString(Byte* byte);
Byte* readByte(FILE* fin);
#endif
