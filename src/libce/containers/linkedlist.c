#include "linkedlist.h"

#include <stdlib.h>

#define LINKED_LIST_INVALID_INDEX 


#define _linkedlist_field(list, field) \
    ((u64*)list)[field]

#define _linkedlist_addr_of(list, index) \
    (void*)(((u64)list) + sizeof(_linkedlist_header) + (index * _linkedlist_field(array, LINKEDLIST_STRIDE)))


linkedlist _linkedlist_create(u64 initial_capacity, u64 stride)
{
    return _linkedlist_create_at(initial_capacity, stride, NULL);
}

linkedlist _linkedlist_create_at(u64 initial_capacity, u64 stride, void* address)
{
    if(!address) return NULL;

    _linkedlist_field(address, LINKEDLIST_HEAD_INDEX) = 0;
    _linkedlist_field(address, LINKEDLIST_TAIL_INDEX) = 0;
    _linkedlist_field(address, LINKEDLIST_LENGTH) = 0;
    _linkedlist_field(address, LINKEDLIST_CAPACITY) = initial_capacity;
    _linkedlist_field(address, LINKEDLIST_STRIDE) = stride;
}

// void _linkedlist_destroy(linkedlist list);

// void _linkedlist_free(linkedlist list);


// b8 _linkedlist_add(linkedlist list, const void* node);

// b8 _linkedlist_insert_at(linkedlist list, const void* node, u64 index);

// b8 _linkedlist_remove(linkedlist list);

// b8 _linkedlist_remove_at(linkedlist list, u64 index);


// void* _linkedlist_get(linkedlist list, u64 index);

// void _linkedlist_set_field(linkedlist list, _linkedlist_field field);

// u64 _linkedlist_get_field(linkedlist list, _linkedlist_field field);