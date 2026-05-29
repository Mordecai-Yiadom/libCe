#include "linkedlist.h"

#include <stdlib.h>
#include "../memutil.h"

#define _linkedlist_field(list, field) \
    ((u64*)list)[field]


#define _linkedlist_addr_of(list, index) \
    (void*)(((u64)list) + sizeof(_linkedlist_header) + (index * _linkedlist_field(list, LINKEDLIST_STRIDE)))


#define linkedlist_node_field(list, index, field) \
    ((u64*)_linkedlist_addr_of(list, index))[field]

#define _linkedlist_is_valid_index(list, index) \
    (index != LINKEDLIST_INVALID_INDEX && index < _linkedlist_field(list, LINKEDLIST_LENGTH))


linkedlist _linkedlist_create(u64 initial_capacity, u64 stride)
{
    return _linkedlist_create_at(initial_capacity, 
        stride, 
        calloc(1, _linkedlistSizeOf(stride, initial_capacity)));
}

linkedlist _linkedlist_create_at(u64 initial_capacity, u64 stride, void* address)
{
    if(!address) return NULL;

    _linkedlist_field(address, LINKEDLIST_HEAD_INDEX) = LINKEDLIST_INVALID_INDEX;
    _linkedlist_field(address, LINKEDLIST_TAIL_INDEX) = LINKEDLIST_INVALID_INDEX;
    _linkedlist_field(address, LINKEDLIST_LENGTH) = 0;
    _linkedlist_field(address, LINKEDLIST_CAPACITY) = initial_capacity;
    _linkedlist_field(address, LINKEDLIST_STRIDE) = stride;

    return address;
}

void _linkedlist_destroy(linkedlist list)
{
    memclear(list, 
        _linkedlistSizeOf(_linkedlist_field(list, LINKEDLIST_STRIDE), 
        _linkedlist_field(list, LINKEDLIST_CAPACITY)));
}

void _linkedlist_free(linkedlist list)
{
    free(list);
}


b8 _linkedlist_add(linkedlist list, const void* node)
{
    if(!list) return 0;
    
    if(_linkedlist_field(list, LINKEDLIST_LENGTH) == _linkedlist_field(list, LINKEDLIST_CAPACITY))
    {
        list = _linkedlist_resize(list, 2 * _linkedlist_field(list, LINKEDLIST_CAPACITY));
    }

    _linkedlist_set(list, _linkedlist_field(list, LINKEDLIST_LENGTH), node);
    _linkedlist_field(list, LINKEDLIST_LENGTH) += 1;
    
    return list;
}

b8 _linkedlist_insert_at(linkedlist list, const void* node, u64 index)
{
    return 0;
}


b8 _linkedlist_set(linkedlist list, u64 index, const void* node)
{
    if(!list) return 0;

    if(!_linkedlist_is_valid_index(list, index)) return 0;

    
}

b8 _linkedlist_remove(linkedlist list)
{
    return 0;
}

b8 _linkedlist_remove_at(linkedlist list, u64 index)
{
    return 0;
}


void* _linkedlist_get(linkedlist list, u64 index)
{
    return NULL;
}

linkedlist _linkedlist_resize(linkedlist list, u64 new_capacity)
{
    if(!list) return NULL;

    linkedlist new_list = realloc(list, 
        _linkedlistSizeOf(_linkedlist_field(list, LINKEDLIST_STRIDE), 
        _linkedlist_field(list, LINKEDLIST_CAPACITY)));
    
    if(!new_list) return list;
    _linkedlist_set_field(new_list, LINKEDLIST_CAPACITY, new_capacity);
    return new_list;
}

void _linkedlist_set_field(linkedlist list, _linkedlist_field field, u64 value)
{
    if(!list) return;
    _linkedlist_field(list, field) = value;
}

u64 _linkedlist_get_field(linkedlist list, _linkedlist_field field)
{
    if(!list) return LINKEDLIST_INVALID_FIELD;
    return _linkedlist_field(list, field);
}