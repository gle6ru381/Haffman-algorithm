#include "readText.h"
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
    temp->sumbol = '\r';
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
