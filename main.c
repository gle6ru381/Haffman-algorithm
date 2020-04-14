#include "readText.h"
#include <malloc.h>
#include <stdio.h>

int main()
{
    FILE* fin = fopen("one.txt", "r");
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

    return 0;
}
