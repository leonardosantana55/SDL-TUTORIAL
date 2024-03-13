//relembra como funciona malloc e realloc

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stddef.h>

typedef struct Vector{
    int x;
    int y;
}Vector;

int main(){

    Vector *old_vector_ptr, *vector_ptr;
    size_t size;

    vector_ptr = (Vector*)malloc(5 * sizeof(Vector));
    size = _msize(vector_ptr);
    printf("size before %u\n", size);

    vector_ptr = realloc(vector_ptr, size + (1*sizeof(Vector)));
    size = _msize(vector_ptr);
    printf("new size is %u", size);

    return 0;
}