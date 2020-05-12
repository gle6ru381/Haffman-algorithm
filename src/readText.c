#include "readText.h"
#include "byte.h"
#include <stdlib.h>

#define CHARCOUNT 127

Vector* readFile(FILE* fin)
{
    if (!fin)
        exit(-3);
    Vector* vector = init_vector();
    uint count[CHARCOUNT] = {0};
    while (!feof(fin)) {
        unsigned char c = (unsigned char)fgetc(fin);
        if (c >= 0 && c <= 126)
            count[c]++;
    }
    for (int i = 0; i < CHARCOUNT; i++) {
        if (count[i]) {
            vector_push_back(vector, newTree(i, &count[i]));
        }
    }
    return vector;
}

HTree* makeTree(Vector* const vec)
{
    HTree* temp = malloc(sizeof(HTree));
    temp->count
            = vec->array[vec->size - 1].count + vec->array[vec->size - 2].count;
    temp->code[0] = '\0';
    temp->sumbol = '\0';
    temp->left = copyTree(&vec->array[vec->size - 1]);
    temp->right = copyTree(&vec->array[vec->size - 2]);

    if (vec->size == 2)
        return temp;
    else {
        for (int i = 0; i < vec->size; i++) {
            if (temp->count > vec->array[i].count) {
                for (int j = vec->size - 1; j > i; j--) {
                    vec->array[j] = vec->array[j - 1];
                }
                vec->array[i] = *temp;
                break;
            }
        }
    }
    vec->size--;
    return makeTree(vec);
}

void makeCode(HTree* const tree)
{
    if (tree->left) {
        strcpy(tree->left->code, tree->code);
        strcat(tree->left->code, "0");
        makeCode(tree->left);
    }
    if (tree->right) {
        strcpy(tree->right->code, tree->code);
        strcat(tree->right->code, "1");
        makeCode(tree->right);
    }
}

void compressFile(FILE* fin, FILE* fout, HTree* tree)
{
    if (!fin || !fout) {
        return;
    }

    unsigned size = 0;
    fwrite(&size, sizeof(unsigned), 1, fout);
    for (char i = 1; i < 127; i++) {
        HTree const* temp = findCode(tree, i);
        if (!temp)
            continue;
        if (temp->sumbol) {
            size += sizeof(uint) + 1;
            fwrite(&i, sizeof(char), 1, fout);
            fwrite(&temp->count, sizeof(uint), 1, fout);
        }
    }
    rewind(fout);
    fwrite(&size, sizeof(unsigned), 1, fout);
    fseek(fout, 0, SEEK_END);
    Byte* byte = byte_init();
    while (!feof(fin)) {
        char c = fgetc(fin);
        if (c < 0 || c > 127)
            continue;
        char const* code = findCode(tree, c)->code;
        while (*code != 0) {
            setBit(byte, *code++);
            if (byte->size == 8) {
                fwrite(&byte->bit, 1, 1, fout);
                byte->size = 0;
                byte->bit = 0;
            }
        }
    }
    if (byte->size) {
        fwrite(&byte->bit, 1, 1, fout);
    }
}

struct Pair {
    char symbol;
    uint count;
};

void decompressFile(FILE* fin, FILE* fout)
{
    if (!fin || !fout)
        return;
    unsigned byteCount = 0;
    fread(&byteCount, sizeof(unsigned), 1, fin);

    Vector* vector = init_vector();
    while (byteCount > 0) {
        struct Pair pair;
        fread(&pair.symbol, sizeof(char), 1, fin);
        fread(&pair.count, sizeof(uint), 1, fin);
        byteCount -= sizeof(char);
        byteCount -= sizeof(uint);
        vector_push_back(vector, newTree(pair.symbol, &pair.count));
    }
    vector_sort(vector);
    HTree* tree = makeTree(vector);
    makeCode(tree);

    Byte* byte;
    char const* code;
    char subCode[22] = {0};
    uchar i1 = 0;
    uchar i2 = 8;

    while (!feof(fin)) {
        if (i2 == 8) {
            byte = byte_init();
            byte->bit = fgetc(fin);
            byte->size = 7;
            code = toString(byte);
            i2 = 0;
        }
        subCode[i1] = code[i2];
        char symbol = treeFindSymbol(tree, subCode, 0);
        if (symbol) {
            fputc(symbol, fout);
            for (int i = 0; i <= i1; i++) {
                subCode[i] = 0;
            }
            i1 = 0;
            i2++;
        } else {
            i1++;
            i2++;
        }
    }
}
