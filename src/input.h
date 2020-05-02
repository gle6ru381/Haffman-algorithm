#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { O_Compress, O_Decompress, O_None } Operation;

typedef struct {
    char* outputFileName;
    char* inputFileName;
    Operation operation;
} Data;

void Error(char* textError);
Data createData(int argc, char** argv);
#endif // INPUT_H
