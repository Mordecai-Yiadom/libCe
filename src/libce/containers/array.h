#ifndef LIBCE_ARRAY_H
#define LIBCE_ARRAY_H

#include "../memtypes.h"

/*  
    An array in libCe is represented as a void*. All the data of the array including the header 
    is at the address which the array points to.
*/
typedef void* array;

typedef enum _array_field
{
    ARRAY_LENGTH = 0,
    ARRAY_STRIDE,
}_array_field;


LIBCE_INTERNAL array _array_create(u64 length, u64 stride);

LIBCE_INTERNAL void _array_destroy(array array);


LIBCE_INTERNAL void _array_set(array array, u64 index, const void* value);

LIBCE_INTERNAL void* _array_get(array array, u64 index);


LIBCE_INTERNAL array _array_resize(array array, u64 new_size);


LIBCE_INTERNAL void _array_set_field(array array, _array_field field, u64 value);

LIBCE_INTERNAL u64 _array_get_field(array array, _array_field field);


/*  
    Allocates a contiguous block memory for the array data and its fields.

    @param
    type type of a given element in the array

    @param
    length number of elements in the array

    @return a pointer to a newly allocated array
*/
#define array_create(type, length) \
    _array_create(length, sizeof(type))


/*  
    Deallocates the given array. Data may or may not be cleared.

    @param
    array array to be destoryed
*/
#define array_destroy(array) \
    _array_destroy(array)



/*  
    Writes the given 'value' to the given array at the given index.

    @param
    array array to be written to

    @param
    index index to write to

    @param
    value value to write
*/
#define array_set(array, index, value)          \
{                                               \
    typeof(value) temp_value = value;           \
    _array_set(array, index, &temp_value);      \
}

/*  
    Retrives the data from the given array at the given index

    @param
    array array to be queried

    @param
    index index to return value of

    @return
    A void* to the value at the given index or NULL if index > array length
*/
#define array_get(array, index) \
    _array_get(array, index)

/*  
    Reallocates the array with the given size

    @param
    array array to be resized

    @param
    new_size desired size of the array

    @return
    A pointer to the newly resized array. 
*/
#define array_resize(array, new_size) \
    _array_resize(array, new_size)


/*  
    Retrieves the length of the given array

    @param
    array array to be queried

    @return
    The size of the given array. May be zero if array == NULL
*/    
#define array_get_length(array) \
    _array_get_field(array, ARRAY_LENGTH)


/*  
    Retrieves the stride of the given array

    @param
    array array to be queried

    @return
    The stride of the given array. May be zero if array == NULL
*/ 
#define array_get_stride(array) \
    _array_get_field(array, ARRAY_STRIDE)

#endif