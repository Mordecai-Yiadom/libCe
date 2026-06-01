#include "arraylist.h"

#include <stdlib.h>
#include "../memutil.h"

#define _arraylist_field(list, field) \
    ((u64*)list)[field]

#define _arraylist_addr_of(list, index) \
    (void*)(((u64)list) + sizeof(_arraylist_header) + (index * _arraylist_field(list, ARRAYLIST_STRIDE)))

arraylist _arraylist_create(u64 initial_capacity, u64 stride)
{
    return _arraylist_create_at(initial_capacity, stride, calloc(1, _arraylistSizeOf(stride, initial_capacity)));
}

arraylist _arraylist_create_at(u64 initial_capacity, u64 stride, void* address)
{   
    if(!address) return NULL;

    _arraylist_field(address, ARRAYLIST_LENGTH) = 0;
    _arraylist_field(address, ARRAYLIST_CAPACITY) = initial_capacity;
    _arraylist_field(address, ARRAYLIST_STRIDE) = stride;

    return address;
}

void _arraylist_destroy(arraylist list)
{
    memclear(list, _arraylist_size(list));
}

void _arraylist_free(arraylist list)
{
    free(list);
}

u64 _arraylist_size(arraylist list)
{
    return _arraylistSizeOf(_arraylist_field(list, ARRAYLIST_STRIDE), _arraylist_field(list, ARRAYLIST_CAPACITY));
}

void _arraylist_set(arraylist list, u64 index, const void* value)
{
    if(!list) return;
    if(index < _arraylist_field(list, ARRAYLIST_LENGTH))
    {
        libce_memcpy(_arraylist_addr_of(list, index), value, _arraylist_field(list, ARRAYLIST_STRIDE));
    }
}

void* _arraylist_get(arraylist list, u64 index)
{
    if(!list) return NULL;

    if(index < _arraylist_field(list, ARRAYLIST_LENGTH))
    {
        return _arraylist_addr_of(list, index);
    }

    return NULL;
}

arraylist _arraylist_push(arraylist list, const void* value)
{
    return _arraylist_push_at(list, _arraylist_field(list, ARRAYLIST_LENGTH), value);
}

arraylist _arraylist_push_at(arraylist list, u64 index, const void* value)
{
    if(!list) return NULL;
    
    if(_arraylist_field(list, ARRAYLIST_LENGTH) == _arraylist_field(list, ARRAYLIST_CAPACITY))
    {   
        list = _arraylist_resize(list, ARRAYLIST_DEFAULT_RESIZE_FACTOR * _arraylist_field(list, ARRAYLIST_CAPACITY));
    }
    
    _arraylist_field(list, ARRAYLIST_LENGTH) += 1;
    
    //Insertion shift up
    for(u64 i = _arraylist_field(list, ARRAYLIST_LENGTH); i > index; i--)
    {   
        //_arraylist_set(list, i, (const void*)_arraylist_addr_of(list, i - 1));
        libce_memcpy(_arraylist_addr_of(list, i), _arraylist_addr_of(list, (i - 1)), _arraylist_field(list, ARRAYLIST_STRIDE));
    }

    _arraylist_set(list, index, value);
    
    return list;
}

void _arraylist_pop(arraylist list, void* dest)
{
    _arraylist_pop_at(list, _arraylist_field(list, ARRAYLIST_LENGTH) - 1, dest);
}

void _arraylist_pop_at(arraylist list, u64 index, void* dest)
{
    if(!list) return;

    if(_arraylist_field(list, ARRAYLIST_LENGTH) < 1) return;

    if(dest) 
        libce_memcpy(dest, 
            _arraylist_addr_of(list, _arraylist_field(list, ARRAYLIST_LENGTH) - 1), 
            _arraylist_field(list, ARRAYLIST_STRIDE));
    
    _arraylist_field(list, ARRAYLIST_LENGTH) -= 1;

    //Deletion shift down
    for(u64 i = index; i < _arraylist_field(list, ARRAYLIST_LENGTH); i++)
    {
        //_arraylist_set(list, i, (const void*)_arraylist_addr_of(list, i + 1));
        libce_memcpy(_arraylist_addr_of(list, i), _arraylist_addr_of(list, (i + 1)), _arraylist_field(list, ARRAYLIST_STRIDE));
    }
}

arraylist _arraylist_pack(arraylist list)
{
    if(!list) return NULL;
    return _arraylist_resize(list, _arraylist_field(list, ARRAYLIST_LENGTH));
}

void _arraylist_clear(arraylist list)
{
    if(!list) return;
    _arraylist_field(list, ARRAYLIST_LENGTH) = 0;
}

// arraylist _arraylist_resize(arraylist list, u64 new_capacity)
// {
//     if(!list) return NULL;

//     u64 new_array_size = _arraylistSizeOf(_arraylist_field(list, ARRAYLIST_STRIDE), new_capacity);
//     arraylist new_array = calloc(1, new_array_size);

//     if(!new_array) return list;

//     libce_memcpy(new_array, list, _arraylistSizeOf(_arraylist_field(list, ARRAYLIST_STRIDE), _arraylist_field(list, ARRAYLIST_CAPACITY)));
//     _arraylist_field(new_array, ARRAYLIST_CAPACITY) = new_capacity;
    
//     free(list);
//     return new_array;
// }

arraylist _arraylist_resize(arraylist list, u64 new_capacity)
{
    if(!list) return NULL;

    arraylist new_array = realloc(list, _arraylistSizeOf(_arraylist_field(list, ARRAYLIST_STRIDE), new_capacity));
    if(!new_array) return list;  

    _arraylist_set_field(new_array, ARRAYLIST_CAPACITY, new_capacity);
    return new_array;   
}


void _arraylist_set_field(arraylist list, _arraylist_field field, u64 value)
{
    if(!list) return;
    _arraylist_field(list, field) = value;
}

u64 _arraylist_get_field(arraylist list, _arraylist_field field)
{
    if(!list) return -1;
    return _arraylist_field(list, field);
} 