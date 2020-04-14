#include "readText.h"
#include <malloc.h>
#include <stdio.h>

int main()
{
    FILE* fin = fopen("abc.txt", "r");
    Vector* vec = readFile(fin);
    vector_sort(vec);
    HTree* total = makeTree(vec);
    vector_free(vec);
    makeCode(total);
    printf("\n%s", findCode(total, '='));

    return 0;
}
