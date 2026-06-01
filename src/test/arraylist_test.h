#ifndef ARRAYLIST_TEST_H
#define ARRAYLIST_TEST_H

#include "../libce/containers/arraylist.h"
#include <stdio.h>
#include <stdlib.h>

void print_arraylist(arraylist list)
{   
    puts("======ARRAYLIST-BEGIN=======");
    printf("arraylist = %p\n", list);
    printf("arraylist->length: %lld\n", arraylist_length(list));
    printf("arraylist->capacity: %lld\n", arraylist_capacity(list));
    printf("arraylist->stride: %lld\n", arraylist_stride(list));
    printf("arraylist (total size in bytes): %lld\n", _arraylistSizeOf(arraylist_stride(list), arraylist_capacity(list)));

    for(u64 i = 0; i < arraylist_length(list); i++)
    {   
        u64* num = (u64*) arraylist_get(list, i);
        printf("arraylist[%lld]=%lld\n", i, *num);
    }
    
    puts("======ARRAYLIST-END=======\n");
}

void test_arraylist()
{   
    u64 size = 5;
    arraylist list = arraylist_reserve(u64, size);
    print_arraylist(list);
    
    for(u64 i = 0; i < size; i++)
    {
        arraylist_push(list, ((u64)(i + 10)));
        print_arraylist(list);
    }

    arraylist_push(list, (u64)67);
    print_arraylist(list);

    arraylist_pop(list, NULL);
    print_arraylist(list);

    arraylist_push_at(list, 2, (u64)69420);
    print_arraylist(list);

    arraylist_pop_at(list, 2, NULL);
    print_arraylist(list);

    // arraylist_push_at(list, 3, 676767);
    // print_arraylist(list);
}


#endif