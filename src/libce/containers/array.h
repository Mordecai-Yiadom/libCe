#ifndef LIBCE_ARRAY_H
#define LIBCE_ARRAY_H

#include "../memtypes.h"

/*  
    An array in libce is represented internally as a void*. All the data of the array including the header 
    is at the address which the array points to.
*/
typedef void* array;

typedef enum _array_field
{
    ARRAY_LENGTH = 0,
    ARRAY_STRIDE,
}_array_field;


array _array_create(u64 length, u64 stride);

void _array_destroy(array array);


void _array_set(array array, u64 index, const void* value);

void* _array_get(array array, u64 index);


array _array_resize(array array, u64 new_size);


void _array_set_field(array array, _array_field field, u64 value);

u64 _array_get_field(array array, _array_field field);



#define array_create(type, length) \
    _array_create(length, sizeof(type))


#define array_destroy(array) \
    _array_destroy(array)


#define array_set(array, index, value)          \
{                                               \
    typeof(value) temp_value = value;           \
    _array_set(array, index, &temp_value);      \
}


#define array_get(array, index) \
    _array_get(array, index)


#define array_resize(array, new_size) \
    _array_resize(array, new_size)


#define array_get_length(array) \
    _array_get_field(array, ARRAY_LENGTH)


#define array_get_stride(array) \
    _array_get_field(array, ARRAY_STRIDE)

#endif