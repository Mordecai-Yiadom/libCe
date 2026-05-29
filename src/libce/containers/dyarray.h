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
    _dyarraySizeOf(sizeof(type), capacity)


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



/*
    Clears the memory at the given dyarray pointer.

    @note
    This function does not free the memory given.

    @param
    array the dyarray to destroy.
*/
#define dyarray_destroy(array) \
    _dyarray_destroy(array)



/*
    Calls 'free()' on the given dyarray pointer.

    @note
    This function does not free the memory

    @param
    array the dyarray to free.
*/
#define dyarray_free(array) \
    _dyarray_free(array)



/*
    Changes the value at a valid index of the given dyarray.

    @param
    array the dyarray to operate on

    @param 
    index the index to set the value into

    @param
    value the value to set on the given index

    @note
    this function will silently fail if the index >= length
*/
#define dyarray_set(array, index, value)          \
{                                                 \
    typeof(value) temp_value = value;             \
    _dyarray_set(array, index, &temp_value);      \
}

/*
    Retrieves the element at a valid index of the given dyarray.

    @param
    array the dyarray to query

    @param 
    index the index to get the element from. 

    @return
    A pointer to the value in the dyarray or NULL if the index or dyarray pointer are invalid

    @note
    this function will silently fail if the index >= length
*/
#define dyarray_get(array, index) \
    _dyarray_get(array, index)


/*
    Adds new element to the end of the dyarray given.

    @param
    array the dyarray to operate on

    @param
    value the value to add to the dyarray

    @note
    this function will silently fail if there is an issue with writing the memory.
*/
#define dyarray_push(array, value)                \
{                                                 \
    typeof(value) temp_value = value;             \
    array = _dyarray_push(array, &temp_value);    \
}


/*
    Removes the last element of the dyarray given.

    @param
    array the dyarray to operate on

    @param
    dest the places to write the popped element to. This may be NULL.
*/
#define dyarray_pop(array, dest)          \
{                                           \
    _dyarray_pop(array, dest);             \
}


/*
    Retrieves the length of the dyarray given.

    @param
    array the dyarray to query.

    @return
    the length of the given dyarray.
*/
#define dyarray_length(array) \
    _dyarray_get_field(array, DYARRAY_LENGTH)

/*
    Retrieves the capacity of the dyarray given.

    @param
    array the dyarray to query.

    @return
    the capacity of the given dyarray.
*/
#define dyarray_capacity(array) \
    _dyarray_get_field(array, DYARRAY_CAPACITY)

/*
    Retrieves the stride of the dyarray given.

    @param
    array the dyarray to query.

    @return
    the stride of the given dyarray.
*/
#define dyarray_stride(array) \
    _dyarray_get_field(array, DYARRAY_STRIDE)


/*
    Retrieves the total size of the dyarray given. This includes the header.

    @param
    array the dyarray to operate on.

    @return
    The total size of the dyarray
*/
#define dyarray_size(array) \
    _dyarray_size(array);

/*
    Resizes the given dyarray's capacity to fit its length.

    @param
    array the dyarray to operate on.
*/
#define dyarray_pack(array) \
    array = _dyarray_pack(array)


/*
    Sets the given dyarray's length to 0, while leaving the capacity intact.

    @param
    array the dyarray to operate on.
*/
#define dyarray_clear(array) \
    _dyarray_set_field(array, DYARRAY_LENGTH, 0)


/*
    Sets the given dyarray's length and capacity to 0. Resizes the 

    @param
    array the dyarray to operate on.
*/   
#define dyarray_reset(array)                      \
{                                                 \
    dyarray_clear(array);                         \
    dyarray_pack(array);                          \
}

#endif