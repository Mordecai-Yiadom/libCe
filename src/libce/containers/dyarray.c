#include "dyarray.h"

#include <stdlib.h>
#include "../memutil.h"

#define _dyarray_field(array, field) \
    ((u64*)array)[field]

#define _dyarray_addr_of(array, index) \
    (void*)(((u64)array) + sizeof(_dyarray_header) + (index * _dyarray_field(array, DYARRAY_STRIDE)))

dyarray _dyarray_create(u64 initial_capacity, u64 stride)
{
    return _dyarray_create_at(initial_capacity, stride, calloc(1, _dyarraySizeOf(stride, initial_capacity)));
}

dyarray _dyarray_create_at(u64 initial_capacity, u64 stride, void* address)
{   
    if(!address) return NULL;

    _dyarray_field(address, DYARRAY_LENGTH) = 0;
    _dyarray_field(address, DYARRAY_CAPACITY) = initial_capacity;
    _dyarray_field(address, DYARRAY_STRIDE) = stride;

    return address;
}

void _dyarray_destroy(dyarray array)
{
    memclear(array, _dyarray_size(array));
}

void _dyarray_free(dyarray array)
{
    free(array);
}

u64 _dyarray_size(dyarray array)
{
    return _dyarraySizeOf(_dyarray_field(array, DYARRAY_STRIDE), _dyarray_field(array, DYARRAY_CAPACITY));
}

void _dyarray_set(dyarray array, u64 index, const void* value)
{
    if(!array) return;
    if(index < _dyarray_field(array, DYARRAY_CAPACITY))
    {
        libce_memcpy(_dyarray_addr_of(array, index), value, _dyarray_field(array, DYARRAY_STRIDE));
    }
}

void* _dyarray_get(dyarray array, u64 index)
{
    if(!array) return NULL;

    if(index < _dyarray_field(array, DYARRAY_LENGTH))
    {
        return _dyarray_addr_of(array, index);
    }

    return NULL;
}

dyarray _dyarray_push(dyarray array, const void* value)
{
    if(!array) return NULL;
    
    if(_dyarray_field(array, DYARRAY_LENGTH) == _dyarray_field(array, DYARRAY_CAPACITY))
    {   
        array = _dyarray_resize(array, DYARRAY_DEFAULT_RESIZE_FACTOR * _dyarray_field(array, DYARRAY_CAPACITY));
    }
    
    _dyarray_set(array, _dyarray_field(array, DYARRAY_LENGTH), value);
    _dyarray_field(array, DYARRAY_LENGTH) += 1;

    return array;
}

void _dyarray_pop(dyarray array, void* dest)
{
    if(!array) return;

    if(_dyarray_field(array, DYARRAY_LENGTH) < 1) return;

    if(dest) 
        libce_memcpy(dest, 
            _dyarray_addr_of(array, _dyarray_field(array, DYARRAY_LENGTH) - 1), 
            _dyarray_field(array, DYARRAY_STRIDE));

    _dyarray_field(array, DYARRAY_LENGTH) -= 1;
}

dyarray _dyarray_pack(dyarray array)
{
    if(!array) return NULL;
    return _dyarray_resize(array, _dyarray_field(array, DYARRAY_LENGTH));
}

void _dyarray_clear(dyarray array)
{
    if(!array) return;
    _dyarray_field(array, DYARRAY_LENGTH) = 0;
}

dyarray _dyarray_resize(dyarray array, u64 new_capacity)
{
    if(!array) return NULL;

    u64 new_array_size = _dyarraySizeOf(_dyarray_field(array, DYARRAY_STRIDE), new_capacity);
    dyarray new_array = calloc(1, new_array_size);

    if(!new_array) return array;

    libce_memcpy(new_array, array, _dyarraySizeOf(_dyarray_field(array, DYARRAY_STRIDE), _dyarray_field(array, DYARRAY_CAPACITY)));
    _dyarray_field(new_array, DYARRAY_CAPACITY) = new_capacity;
    
    free(array);
    return new_array;
}




// dyarray _dyarray_resize(dyarray array, u64 new_capacity)
// {
//     if(!array) return NULL;

//     dyarray new_array = realloc(array, _dyarraySizeOf(_dyarray_field(array, DYARRAY_STRIDE), new_capacity));
//     if(!new_array) return array;  

//     _dyarray_set_field(new_array, DYARRAY_CAPACITY, new_capacity);
//     return new_array;   
// }


void _dyarray_set_field(dyarray array, _dyarray_field field, u64 value)
{
    if(!array) return;
    _dyarray_field(array, field) = value;
}

u64 _dyarray_get_field(dyarray array, _dyarray_field field)
{
    if(!array) return -1;
    return _dyarray_field(array, field);
} 