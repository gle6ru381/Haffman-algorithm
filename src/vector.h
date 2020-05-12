#ifndef LIST_H
#define LIST_H

#include "htree.h"
#include <stdbool.h>
#include <string.h>

struct Vector {
    struct HTree* array;
    uchar size;
    uchar capacity;
};

typedef struct Vector Vector;

Vector* init_vector();
bool vector_push_back(Vector* vec, HTree* const tree);
void vector_sort(Vector* const vector);
void vector_free(Vector* vector);

#endif
