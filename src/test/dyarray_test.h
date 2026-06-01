#ifndef DYARRAY_TEST_H
#define DYARRAY_TEST_H

#include "../libce/containers/dyarray.h"
#include <stdio.h>
#include <stdlib.h>

void print_dyarray(dyarray array)
{   
    puts("======DYARRAY-BEGIN=======");
    printf("dyarray = %p\n", array);
    printf("dyarray->length: %lld\n", dyarray_length(array));
    printf("dyarray->capacity: %lld\n", dyarray_capacity(array));
    printf("dyarray->stride: %lld\n", dyarray_stride(array));
    printf("dyarray (total size in bytes): %lld\n", _dyarraySizeOf(dyarray_stride(array), dyarray_capacity(array)));

    for(u64 i = 0; i < dyarray_length(array); i++)
    {   
        u64* num = dyarray_get(array, i);
        printf("dyarray[%lld]=%lld\n", i, *num);
    }
    
    puts("======DYARRAY-END=======\n");
}

void test_dyarray()
{   
    u64 size = 10;
    dyarray array = dyarray_reserve(u64, size);
    print_dyarray(array);
    
    for(u64 i = 0; i < size * 4; i++)
    {
        dyarray_push(array, i + 10);
        print_dyarray(array);
    }

    dyarray_set(array, 0, 67);
    print_dyarray(array);


    dyarray_push(array, 20);
    print_dyarray(array);

    dyarray_pop(array, NULL);
    print_dyarray(array);

    dyarray_reset(array);
    print_dyarray(array);
    //dyarray_destroy(array);
}


#endif