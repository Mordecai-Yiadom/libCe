#ifndef LIBCE_ARRAYLIST_H
#define LIBCE_ARRAYLIST_H

#include "../memtypes.h"

typedef void* arraylist;

typedef enum _arraylist_field
{
    ARRAYLIST_LENGTH = 0,
    ARRAYLIST_CAPACITY = 1,
    ARRAYLIST_STRIDE = 2,
}_arraylist_field;

typedef struct _arraylist_header
{   
    u64 length;
    u64 capacity;
    u64 stride;
}_arraylist_header;


LIBCE_INTERNAL arraylist _arraylist_create(u64 initial_capacity, u64 stride);

LIBCE_INTERNAL arraylist _arraylist_create_at(u64 initial_capacity, u64 stride, void* address);

LIBCE_INTERNAL void _arraylist_destroy(arraylist list);

LIBCE_INTERNAL void _arraylist_free(arraylist list);


LIBCE_INTERNAL void _arraylist_set(arraylist list, u64 index, const void* value);

LIBCE_INTERNAL void* _arraylist_get(arraylist list, u64 index);

LIBCE_INTERNAL arraylist _arraylist_push(arraylist list, const void* value);

LIBCE_INTERNAL arraylist _arraylist_push_at(arraylist list, u64 index, const void* value);

LIBCE_INTERNAL void _arraylist_pop(arraylist list, void* dest);

LIBCE_INTERNAL void _arraylist_pop_at(arraylist list, u64 index, void* dest);




LIBCE_INTERNAL arraylist _arraylist_pack(arraylist list);

LIBCE_INTERNAL void _arraylist_clear(arraylist list);

LIBCE_INTERNAL arraylist _arraylist_resize(arraylist list, u64 new_capacity);


LIBCE_INTERNAL u64 _arraylist_size(arraylist list);

LIBCE_INTERNAL void _arraylist_set_field(arraylist list, _arraylist_field field, u64 value);

LIBCE_INTERNAL u64 _arraylist_get_field(arraylist list, _arraylist_field field); 


#define ARRAYLIST_DEFAULT_RESIZE_FACTOR 2
#define ARRAYLIST_DEFAULT_CAPACITY 1


#define _arraylistSizeOf(stride, capacity) \
    ((u64)(sizeof(_arraylist_header) + (stride * capacity)))

#define arraylistSizeOf(type, capacity) \
    _arraylistSizeOf(sizeof(type), capacity)


/*
    Allocates and initializes a arraylist on the heap and sets the initial values 'capacity' = 1 and 'length' = 0

    @param
    type type of element the arraylist will contain.

    @return
    A pointer to a newly allocated arraylist
*/
#define arraylist_create(type) \
    _arraylist_create(ARRAYLIST_DEFAULT_CAPACITY, sizeof(type))


/*
    Allocates and initializes a arraylist on the heap and sets the initial length to 0.

    @param
    type type of element the arraylist will contain.

    @param
    initial_capacity the starting amount of elements (not including the header) for the arraylist 
*/
#define arraylist_reserve(type, initial_capacity) \
    _arraylist_create(((initial_capacity > 0) ? initial_capacity : ARRAYLIST_DEFAULT_CAPACITY), sizeof(type))


/*
    Initializes a arraylist at the given address and sets the initial values 'capacity' = 1 and 'length' = 0

    @param
    type type of element the arraylist will contain.

    @param
    address address to initialize arraylist at

    @return
    A pointer to a newly allocated arraylist
*/
#define arraylist_create_at(type, address) \
    _arraylist_create_at(ARRAYLIST_DEFAULT_CAPACITY, sizeof(type), address)


/*
    Initializes a arraylist at the given address and sets the initial length to 0.

    @param
    type type of element the arraylist will contain.

    @param
    address address to initialize arraylist at

    @param
    initial_capacity the starting amount of elements (not including the header) for the arraylist 
*/
#define arraylist_reserve_at(type, initial_capacity, address) \
    _arraylist_create_at(((initial_capacity > 0) ? initial_capacity : ARRAYLIST_DEFAULT_CAPACITY), sizeof(type), address)



/*
    Clears the memory at the given arraylist pointer.

    @note
    This function does not free the memory given.

    @param
    list the arraylist to destroy.
*/
#define arraylist_destroy(list) \
    _arraylist_destroy(list)



/*
    Calls 'free()' on the given arraylist pointer.

    @note
    This function does not free the memory

    @param
    list the arraylist to free.
*/
#define arraylist_free(list) \
    _arraylist_free(list)



/*
    Changes the value at a valid index of the given arraylist.

    @param
    list the arraylist to operate on

    @param 
    index the index to set the value into

    @param
    value the value to set on the given index

    @note
    this function will silently fail if the index >= length
*/
#define arraylist_set(list, index, value)          \
{                                                 \
    typeof(value) temp_value = value;             \
    _arraylist_set(list, index, &temp_value);      \
}

/*
    Retrieves the element at a valid index of the given arraylist.

    @param
    list the arraylist to query

    @param 
    index the index to get the element from. 

    @return
    A pointer to the value in the arraylist or NULL if the index or arraylist pointer are invalid

    @note
    this function will silently fail if the index >= length
*/
#define arraylist_get(list, index) \
    _arraylist_get(list, index)


/*
    Adds new element to the end of the arraylist given.

    @param
    list the arraylist to operate on

    @param
    value the value to add to the arraylist

    @note
    this function will silently fail if there is an issue with writing the memory.
*/
#define arraylist_push(list, value)                \
{                                                 \
    typeof(value) temp_value = value;             \
    list = _arraylist_push(list, &temp_value);    \
}

#define arraylist_push_at(list, index, value)               \
{                                                           \
    typeof(value) temp_value = value;                       \
    list = _arraylist_push_at(list, index, &temp_value);    \
}



/*
    Removes the last element of the arraylist given.

    @param
    list the arraylist to operate on

    @param
    dest the places to write the popped element to. This may be NULL.
*/
#define arraylist_pop(list, dest)          \
{                                           \
    _arraylist_pop(list, dest);             \
}


#define arraylist_pop_at(list, index, dest)          \
{                                           \
    _arraylist_pop_at(list, index, dest);             \
}


/*
    Retrieves the length of the arraylist given.

    @param
    list the arraylist to query.

    @return
    the length of the given arraylist.
*/
#define arraylist_length(list) \
    _arraylist_get_field(list, ARRAYLIST_LENGTH)

/*
    Retrieves the capacity of the arraylist given.

    @param
    list the arraylist to query.

    @return
    the capacity of the given arraylist.
*/
#define arraylist_capacity(list) \
    _arraylist_get_field(list, ARRAYLIST_CAPACITY)

/*
    Retrieves the stride of the arraylist given.

    @param
    list the arraylist to query.

    @return
    the stride of the given arraylist.
*/
#define arraylist_stride(list) \
    _arraylist_get_field(list, ARRAYLIST_STRIDE)


/*
    Retrieves the total size of the arraylist given. This includes the header.

    @param
    list the arraylist to operate on.

    @return
    The total size of the arraylist
*/
#define arraylist_size(list) \
    _arraylist_size(list);

/*
    Resizes the given arraylist's capacity to fit its length.

    @param
    list the arraylist to operate on.
*/
#define arraylist_pack(list) \
    list = _arraylist_pack(list)


/*
    Sets the given arraylist's length to 0, while leaving the capacity intact.

    @param
    list the arraylist to operate on.
*/
#define arraylist_clear(list) \
    _arraylist_set_field(list, ARRAYLIST_LENGTH, 0)


/*
    Sets the given arraylist's length and capacity to 0. Resizes the 

    @param
    list the arraylist to operate on.
*/   
#define arraylist_reset(list)                      \
{                                                 \
    arraylist_clear(list);                         \
    arraylist_pack(list);                          \
}

#endif