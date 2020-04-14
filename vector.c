#include "vector.h"
#include <malloc.h>

Vector* init_vector()
{
    Vector* vec = malloc(sizeof(Vector));
    if (!vec) {
        return NULL;
    }
    vec->array = NULL;
    vec->size = 0;
    vec->capacity = 0;
    return vec;
}

bool vector_push_back(Vector* vec, HTree* tree)
{
    if (vec->size == vec->capacity) {
        HTree* temp = realloc(vec->array, (vec->capacity + 10) * sizeof(HTree));
        if (temp == NULL)
            return false;
        vec->capacity += 10;
        vec->array = temp;
    }
    vec->array[vec->size++] = *tree;
    return true;
}

void swap(HTree* first, HTree* second)
{
    HTree temp = *first;
    *first = *second;
    *second = temp;
}

void vector_sort(Vector* vec)
{
    for (int i = 0; i < vec->size; i++) {
        for (int j = 0; j < vec->size - 1; j++) {
            if (vec->array[j].count < vec->array[j + 1].count)
                swap(&vec->array[j], &vec->array[j + 1]);
        }
    }
}

void vector_free(Vector* vector)
{
    if (vector->array)
        free(vector->array);
    free(vector);
}
