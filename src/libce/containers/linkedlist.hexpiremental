#ifndef LIBCE_LINKEDLIST_H
#define LIBCE_LINKEDLIST_H

#include "../memtypes.h"

#define LINKEDLIST_INVALID_INDEX INT64_MAX 
#define LINKEDLIST_INVALID_FIELD INT64_MAX 

typedef void* linkedlist;

typedef struct _linkedlist_header
{
    u64 head_index;
    u64 tail_index;
    u64 length;
    u64 capacity;
    u64 stride;
}_linkedlist_header;

typedef enum _linkedlist_field
{
    LINKEDLIST_HEAD_INDEX = 0,
    LINKEDLIST_TAIL_INDEX,
    LINKEDLIST_LENGTH,
    LINKEDLIST_CAPACITY,
    LINKEDLIST_STRIDE, 
}_linkedlist_field;


typedef struct _linkedlist_node_header
{
    u64 prev_index;
    u64 next_index;
}_linkedlist_node_header;

typedef enum _linkedlist_node_field
{
    LINKEDLISTNODE_PREV_INDEX = 0,
    LINKEDLISTNODE_NEXT_INDEX,
    LINKEDLISTNODE_DATA
}_linkedlist_node_field;



#define _linkedlistSizeOf(stride, capacity) \
    ((u64)(sizeof(_linkedlist_header) + ((sizeof(_linkedlist_node_header) + stride) * capacity)))

#define linkedlistSizeOf(type, capacity) \
    _linkedlistSizeOf(sizeof(type), capacity)


LIBCE_INTERNAL linkedlist _linkedlist_create(u64 initial_capacity, u64 stride);

LIBCE_INTERNAL linkedlist _linkedlist_create_at(u64 initial_capacity, u64 stride, void* address);

LIBCE_INTERNAL void _linkedlist_destroy(linkedlist list);

LIBCE_INTERNAL void _linkedlist_free(linkedlist list);


LIBCE_INTERNAL b8 _linkedlist_add(linkedlist list, const void* node);

LIBCE_INTERNAL b8 _linkedlist_insert_at(linkedlist list, const void* node, u64 index);

LIBCE_INTERNAL b8 _linkedlist_set(linkedlist list, u64 index, const void* node);

LIBCE_INTERNAL b8 _linkedlist_remove(linkedlist list);

LIBCE_INTERNAL b8 _linkedlist_remove_at(linkedlist list, u64 index);


LIBCE_INTERNAL void* _linkedlist_get(linkedlist list, u64 index);

LIBCE_INTERNAL linkedlist _linkedlist_resize(linkedlist, u64 new_capacity);


LIBCE_INTERNAL void _linkedlist_set_field(linkedlist list, _linkedlist_field field, u64 value);

LIBCE_INTERNAL u64 _linkedlist_get_field(linkedlist list, _linkedlist_field field);





#endif