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
            vector_push_back(vector, newTree(i, count[i]));
        }
    }
    return vector;
}

HTree* makeTree(Vector* vec)
{
    HTree* temp = malloc(sizeof(HTree));
    temp->count
            = vec->array[vec->size - 1].count + vec->array[vec->size - 2].count;
    temp->code[0] = '\0';
    temp->sumbol = '\0';
    temp->left = copyTree(vec->array[vec->size - 1]);
    temp->right = copyTree(vec->array[vec->size - 2]);

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

void makeCode(HTree* tree)
{
    if (tree->left) {
        strcpy(tree->left->code, tree->code);
        strcat(tree->left->code, "0");
        if (tree->left->sumbol != '\r') {
            printf("code: %s\tsymbol: %c\n",
                   tree->left->code,
                   tree->left->sumbol);
        }
        makeCode(tree->left);
    }
    if (tree->right) {
        strcpy(tree->right->code, tree->code);
        strcat(tree->right->code, "1");
        if (tree->right->sumbol != '\r') {
            printf("code: %s\tsymbol: %c\n",
                   tree->right->code,
                   tree->right->sumbol);
        }
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
        char const* str = findCode(tree, i);
        if (str) {
            size += strlen(str) + 2;
            fwrite(&i, sizeof(char), 1, fout);
            fwrite(str, sizeof(char), strlen(str) + 1, fout);
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
        char const* code = findCode(tree, c);
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
    char code[22];
};

char findSymbol(struct Pair pair[], char const* code)
{
    for (int i = 0; i < 127; i++) {
        if (pair[i].symbol == 0)
            break;
        if (!strcmp(pair[i].code, code))
            return pair[i].symbol;
    }
    return 0;
}

void decompressFile(FILE* fin, FILE* fout)
{
    if (!fin || !fout)
        return;
    unsigned countByte;
    fread(&countByte, sizeof(unsigned), 1, fin);

    struct Pair pair[127];
    int i = 0;
    while (countByte) {
        char symbol;
        fread(&symbol, 1, 1, fin);
        pair[i].symbol = symbol;
        countByte--;

        char codeByte = 0;
        int j = 0;
        do {
            fread(&codeByte, 1, 1, fin);
            pair[i].code[j] = codeByte;
            j++;
            countByte--;
        } while (codeByte != 0);
        i++;
    }
    char* code = malloc(sizeof(char));
    Byte* byte;
    char subCode[22] = {0};
    int i1 = 0;
    int i2 = 8;
    while (!feof(fin)) {
        if (i2 == 8) {
            free(code);
            byte = readByte(fin);
            code = toString(byte);
            free(byte);
            i2 = 0;
        }
        subCode[i1] = code[i2];
        char sym = findSymbol(pair, subCode);
        if (sym) {
            fputc(sym, fout);
            for (int j = 0; j <= i1; j++) {
                subCode[j] = 0;
            }
            i1 = 0;
            i2++;
        } else {
            i1++;
            i2++;
        }
    }
}
