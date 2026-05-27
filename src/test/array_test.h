#ifndef ARRAY_TEST_H
#define ARRAY_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include "../libce/containers/array.h"

typedef struct position_component
{
    f32 x, y, z;
}position_component;

typedef struct entity
{
    u64 id;
    f32 health;
    position_component position;
}entity;

void print_array(array array, FILE* fd)
{
    fputs("\n======ARRAY-BEGIN=======\n", fd);
    fprintf(fd, "array->length: %lld\n", array_length(array));
    fprintf(fd, "array->stride: %lld\n", array_stride(array));
    fprintf(fd, "array (total size in bytes): %lld\n", _arraySizeOf(array_stride(array), array_length(array)));    
    fputs("======ARRAY-END=======\n", fd);
}

void test_array()
{   
    #define INIT_SIZE 17000
    #define RESIZE_SIZE 31313131

    array myArray = array_create(entity, INIT_SIZE);
    //FILE* logFile = fopen("log", "wb");
    
    for(u64 i = 0; i < array_length(myArray); i++)
    {   
        entity ent = {.id=i, .health=i*10};
        ent.position = (position_component){.x=i+9, .y=i/2, .z=i+1};

        array_set(myArray, i, ent);
    }

    

    puts("Ran");
    array_resize(myArray, RESIZE_SIZE);
    print_array(myArray, stdout);

    for(u64 i = 0; i < array_length(myArray); i++)
    {   
        entity* e = (entity*) array_get(myArray, i);
        printf("myArray[%lld].health = %.2f\n", i, e->health);
    }

    //array_destroy(myArray);
}

#endif