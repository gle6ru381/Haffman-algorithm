#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned uint;

void Error(char* textError)
{
    fprintf(stderr, "%s", textError);
    exit(EXIT_FAILURE);
}

Data createData(int argc, char** argv)
{
    Operation operation = O_None;
    char* outputFileName = NULL;
    char* inputFileName = NULL;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-o")) {
            if (i == argc - 1) {
                Error("Input output file after -o");
            } else if (outputFileName) {
                Error("Double definition output file");
            } else if (argv[i + 1][0] == '-') {
                Error("Syntax error");
            } else {
                uint length = strlen(argv[i + 1]);
                outputFileName = malloc((length + 1) * sizeof(char));
                strcpy_s(
                        outputFileName,
                        (length + 1) * sizeof(char),
                        argv[i + 1]);
                i++;
            }
        } else if (!strcmp(argv[i], "-c")) {
            if (operation != O_None) {
                Error("Double definition operation type");
            }
            operation = O_Compress;
        } else if (!strcmp(argv[i], "-d")) {
            if (operation != O_None) {
                Error("Double definition operation type");
            }
            operation = O_Decompress;
        } else {
            if (inputFileName) {
                Error("Double definition input file");
            }
            uint length = strlen(argv[i]);
            inputFileName = malloc((length + 1) * sizeof(char));
            strcpy_s(inputFileName, (length + 1) * sizeof(char), argv[i]);
        }
    }
    if (operation == O_None) {
        Error("Operation not declared");
    }
    if (!inputFileName) {
        Error("Input file not declared");
    }
    if (!outputFileName) {
        uint length = strlen(inputFileName);
        outputFileName = malloc(length * sizeof(char) + 3);
        uint i = 0;
        for (; inputFileName[i] != '.'; i++) {
            outputFileName[i] = inputFileName[i];
        }
        if (operation == O_Compress)
            memcpy(outputFileName + i, ".dat", 5);
        else
            memcpy(outputFileName + i, ".txt", 5);
    }
    Data data = {outputFileName, inputFileName, operation};

    return data;
}
