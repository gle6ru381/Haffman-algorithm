#ifndef READTEXT_H
#define READTEXT_H

#include "vector.h"
#include <stdio.h>

Vector* readFile(FILE* fin);
HTree* makeTree(Vector* vec);
void makeCode(HTree* tree);
void compressFile(FILE* fin, HTree* tree);

#endif
