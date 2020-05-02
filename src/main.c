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
        Vector* vec = readFile(fin);
        vector_sort(vec);
        HTree* total = makeTree(vec);
        vector_free(vec);
        makeCode(total);

        rewind(fin);
        FILE* fout = fopen(data.outputFileName, "wb");
        if (!fout) {
            Error("Output file not open");
        }
        compressFile(fin, fout, total);
    } else {
        FILE* fin = fopen(data.inputFileName, "rb");
        if (!fin) {
            Error("Input file not open");
        }
        FILE* fout = fopen(data.outputFileName, "w");
        decompressFile(fin, fout);
    }
    /*   FILE* fin = fopen("one.txt", "r");
       Vector* vec = readFile(fin);
       vector_sort(vec);
       HTree* total = makeTree(vec);
       vector_free(vec);
       makeCode(total);

       rewind(fin);
       FILE* fout = fopen("abc.dat", "wb");

       compressFile(fin, fout, total);
       fclose(fout);
       fclose(fin);
       fin = fopen("abc.dat", "rb");
       fout = fopen("result.txt", "w");
       printf("\n\n");
       decompressFile(fin, fout);
   */
    return 0;
}
