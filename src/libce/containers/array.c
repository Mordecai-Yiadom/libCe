#include "array.h"

#include <stdlib.h>
#include "../memutil.h"
#include <stdio.h>

#define _array_field(array, field) \
    ((u64*)array)[field]

#define _array_addr_of(array, index)  \
    ((void*)(((u64)array) + sizeof(_array_header) + (index * _array_field(array, ARRAY_STRIDE))))

#define _array_is_valid_index(length, index) \
    (index < length)


array _array_create(u64 length, u64 stride)
{   
    return _array_create_at(length, stride, calloc(1, _arraySizeOf(stride, length)));
}

array _array_create_at(u64 length, u64 stride, void* heap_address)
{
    if(!heap_address) return NULL;

    _array_field(heap_address, ARRAY_LENGTH) = length;
    _array_field(heap_address, ARRAY_STRIDE) = stride;
    
    return heap_address;
}


void _array_destroy(array array)
{
    free(array);
}

void _array_set(array array, u64 index, const void* value)
{
    if(!array) return;

    if(!_array_is_valid_index(((_array_header*)array)->length, index)) return;
        
    libce_memcpy(_array_addr_of(array, index), value, _array_field(array, ARRAY_STRIDE));
}

void* _array_get(array array, u64 index)
{
    if(!array) return NULL;

    if(!_array_is_valid_index(_array_field(array, ARRAY_LENGTH), index)) 
        return NULL;

    return _array_addr_of(array, index);
}

// array _array_resize(array arr, u64 new_size)
// {
//     if(!arr) return NULL;
//     u64 new_array_size = _arraySizeOf(_array_field(arr, ARRAY_STRIDE), new_size);
//     array new_array = calloc(1, new_array_size);

//     libce_memcpy(new_array, arr, _array_field(arr, ARRAY_LENGTH));

//     if(new_array)
//         _array_set_field(new_array, ARRAY_LENGTH, new_size);

//     free(arr);
//     return new_array;
// }

array _array_resize(array array, u64 new_size)
{
    if(!array) return NULL;
    array = realloc(array, _arraySizeOf(_array_field(array, ARRAY_STRIDE), new_size));

    _array_set_field(array, ARRAY_LENGTH, new_size);
    return array;
}



void _array_set_field(array array, _array_field field, u64 value)
{
    if(!array) return;
    _array_field(array, field) = value;
}


u64 _array_get_field(array array, _array_field field)
{   
    if(!array) return -1;
    return _array_field(array, field);
}
