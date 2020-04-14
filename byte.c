#include "byte.h"
#include <malloc.h>
#include <stddef.h>

Byte* byte_init()
{
    Byte* byte = malloc(sizeof(Byte));
    if (!byte)
        return NULL;
    byte->bit = 0;
    byte->size = 0;
    return byte;
}

void setBit(Byte* byte, char bit)
{
    byte->bit |= ((bit - '0') << (7 - byte->size));
    byte->size++;
}

char* toString(Byte* byte)
{
    char* str = calloc(8, sizeof(char));
    if (!str)
        return NULL;
    for (int i = 0; i < 8; i++) {
        str[i] = (1 & (byte->bit >> (byte->size - i))) + '0';
    }
    return str;
}

Byte* readByte(FILE* fin)
{
    Byte* byte = byte_init();
    fread(&byte->bit, 1, 1, fin);
    byte->size = 7;
    return byte;
}
