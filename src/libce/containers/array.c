#include "array.h"

#include <stdlib.h>
#include <string.h>

#define _array_calc_offset(array, index, stride)  \
    (void*)(((u64)array) + sizeof(_array_header) + (index * stride))


#define _array_is_valid_index(length, index) (index < length)

typedef struct _array_header
{
    u64 length;
    u64 stride;
}_array_header;


array _array_create(u64 length, u64 stride)
{   
    u64 totalSize = sizeof(_array_header) + (length * stride);
    array array = calloc(1, totalSize);

    ((_array_header*)array)->length = length;
    ((_array_header*)array)->stride = stride;
    
    return array;
}

void _array_destroy(array array)
{
    free(array);
}

void _array_set(array array, u64 index, const void* value)
{
    if(!array) return;

    if(!_array_is_valid_index(((_array_header*)array)->length, index)) return;
        
    //For now, this function uses the standard lib 'memcpy' until libce has its own
    memcpy(_array_calc_offset(array, index, ((_array_header*)array)->stride), 
            value, 
            ((_array_header*)array)->stride);
}

void* _array_get(array array, u64 index)
{
    if(!array) return NULL;

    if(!_array_is_valid_index(((_array_header*)array)->length, index)) 
        return NULL;

    return _array_calc_offset(array, index, ((_array_header*)array)->stride);
}

array _array_resize(array array, u64 new_size)
{
    if(!array) return NULL;

    void* new_array = realloc(array, new_size);
    
    if(new_array)
        _array_set_field(new_array, ARRAY_LENGTH, new_size); 

    return new_array;
}

void _array_set_field(array array, _array_field field, u64 value)
{
    if(!array) return;
    ((u64*)array)[field] = value;
}


u64 _array_get_field(array array, _array_field field)
{   
    if(!array) return 0;
    return ((u64*)array)[field];
}
