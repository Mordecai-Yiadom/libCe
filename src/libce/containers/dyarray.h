#ifndef LIBCE_DYARRAY_H
#define LIBCE_DYARRAY_H

#include "../memtypes.h"

typedef void* dyarray;

typedef enum _dyarray_field
{
    DYARRAY_LENGTH = 0,
    DYARRAY_CAPACITY = 1,
    DYARRAY_STRIDE = 2,
}_dyarray_field;

typedef struct _dyarray_header
{   
    u64 length;
    u64 capacity;
    u64 stride;
}_dyarray_header;


//typedef struct _dyarray_header _dyarray_header;

LIBCE_INTERNAL dyarray _dyarray_create(u64 initial_capacity, u64 stride);

LIBCE_INTERNAL dyarray _dyarray_create_at(u64 initial_capacity, u64 stride, void* address);

LIBCE_INTERNAL void _dyarray_destroy(dyarray array);

LIBCE_INTERNAL void _dyarray_free(dyarray array);


LIBCE_INTERNAL void _dyarray_set(dyarray array, u64 index, const void* value);

LIBCE_INTERNAL void* _dyarray_get(dyarray array, u64 index);

LIBCE_INTERNAL dyarray _dyarray_push(dyarray array, const void* value);

LIBCE_INTERNAL void _dyarray_pop(dyarray array, void* dest);


LIBCE_INTERNAL dyarray _dyarray_pack(dyarray array);

LIBCE_INTERNAL void _dyarray_clear(dyarray array);

LIBCE_INTERNAL dyarray _dyarray_resize(dyarray array, u64 new_capacity);


LIBCE_INTERNAL u64 _dyarray_size(dyarray array);

LIBCE_INTERNAL void _dyarray_set_field(dyarray array, _dyarray_field field, u64 value);

LIBCE_INTERNAL u64 _dyarray_get_field(dyarray array, _dyarray_field field); 


#define DYARRAY_DEFAULT_RESIZE_FACTOR 2
#define DYARRAY_DEFAULT_CAPACITY 1


#define _dyarraySizeOf(stride, capacity) \
    ((u64)(sizeof(_dyarray_header) + (stride * capacity)))

#define dyarraySizeOf(type, capacity) \
    ((u64)(sizeof(_dyarray_header) + (sizeof(type) * capacity)))


/*
    Allocates and initializes a dyarray on the heap and sets the initial values 'capacity' = 1 and 'length' = 0

    @param
    type type of element the dyarray will contain.

    @return
    A pointer to a newly allocated dyarray
*/
#define dyarray_create(type) \
    _dyarray_create(DYARRAY_DEFAULT_CAPACITY, sizeof(type))


/*
    Allocates and initializes a dyarray on the heap and sets the initial length to 0.

    @param
    type type of element the dyarray will contain.

    @param
    initial_capacity the starting amount of elements (not including the header) for the dyarray 
*/
#define dyarray_reserve(type, initial_capacity) \
    _dyarray_create(((initial_capacity > 0) ? initial_capacity : DYARRAY_DEFAULT_CAPACITY), sizeof(type))


/*
    Initializes a dyarray at the given address and sets the initial values 'capacity' = 1 and 'length' = 0

    @param
    type type of element the dyarray will contain.

    @param
    address address to initialize dyarray at

    @return
    A pointer to a newly allocated dyarray
*/
#define dyarray_create_at(type, address) \
    _dyarray_create_at(DYARRAY_DEFAULT_CAPACITY, sizeof(type), address)


/*
    Initializes a dyarray at the given address and sets the initial length to 0.

    @param
    type type of element the dyarray will contain.

    @param
    address address to initialize dyarray at

    @param
    initial_capacity the starting amount of elements (not including the header) for the dyarray 
*/
#define dyarray_reserve_at(type, initial_capacity, address) \
    _dyarray_create_at(((initial_capacity > 0) ? initial_capacity : DYARRAY_DEFAULT_CAPACITY), sizeof(type), address)


#define dyarray_destroy(array) \
    _dyarray_destroy(array)


#define dyarray_free(array) \
    _dyarray_free(array)


#define dyarray_set(array, index, value)          \
{                                                 \
    typeof(value) temp_value = value;             \
    _dyarray_set(array, index, &temp_value);      \
}

#define dyarray_get(array, index) \
    _dyarray_get(array, index)


#define dyarray_push(array, value)                \
{                                                 \
    typeof(value) temp_value = value;             \
    array = _dyarray_push(array, &temp_value);    \
}

#define dyarray_pop(array, value)          \
{                                           \
    _dyarray_pop(array, value);             \
}

#define dyarray_length(array) \
    _dyarray_get_field(array, DYARRAY_LENGTH)

#define dyarray_capacity(array) \
    _dyarray_get_field(array, DYARRAY_CAPACITY)

#define dyarray_stride(array) \
    _dyarray_get_field(array, DYARRAY_STRIDE)


#define dyarray_pack(array) \
    array = _dyarray_pack(array)


#define dyarray_clear(array) \
    _dyarray_set_field(array, DYARRAY_LENGTH, 0)


#define dyarray_reset(array)                      \
{                                                 \
    dyarray_clear(array);                         \
    dyarray_pack(array);                          \
}

#define dyarray_size(array) \
    _dyarray_size(array);

#endif