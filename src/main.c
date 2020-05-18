#include "input.h"
#include "readText.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    Data data = createData(argc, argv);

    if (data.operation == O_Compress) {
        FILE* fin = fopen(data.inputFileName, "r");
        if (!fin) {
            Error("Input file not open");
        }
        free(data.inputFileName);
        Vector* vec = readFile(fin);
        if (!vec) {
            Error("bad alloc");
        }
        vector_sort(vec);
        HTree* total = makeTree(vec);
        vector_free(vec);
        makeCode(total);

        rewind(fin);
        FILE* fout = fopen(data.outputFileName, "wb");
        if (!fout) {
            Error("Output file not open");
        }
        free(data.outputFileName);
        compressFile(fin, fout, total);
    } else {
        FILE* fin = fopen(data.inputFileName, "rb");
        if (!fin) {
            Error("Input file not open");
        }
        free(data.inputFileName);
        FILE* fout = fopen(data.outputFileName, "w");
        if (!fin) {
            Error("Ouput file not open");
        }
        free(data.outputFileName);
        decompressFile(fin, fout);
    }
    return 0;
}
