//relembra como funciona malloc e realloc

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stddef.h>

typedef struct Vector{
    int x;
    int y;
    size_t size;
}Vector;

Vector* createVector();

int main(){

    //Vector *old_vector_ptr, *vector_ptr;
    //size_t size;

    //vector_ptr = (Vector*)malloc(5 * sizeof(Vector));
    //size = _msize(vector_ptr);
    
    Vector *vector_ptr = createVector();
    printf("size before %u\n", vector_ptr->size);
/* 
    vector_ptr = realloc(vector_ptr, size + (1*sizeof(Vector)));
    size = _msize(vector_ptr);
    printf("new size is %u", size);
 */
    return 0;
}

Vector* createVector(){
    Vector *v_ptr;
    v_ptr = (Vector*)malloc(5 * sizeof(Vector));
    v_ptr->size = _msize(v_ptr);
    return v_ptr;
}