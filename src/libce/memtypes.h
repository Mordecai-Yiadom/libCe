#ifndef LIBCE_MEMTYPES_H
#define LIBCE_MEMETYPES_H

#include <inttypes.h>
#include <stdbool.h>

#define LIBCE_API extern
#define LIBCE_INTERNAL extern

typedef uint8_t unsigned_byte;

typedef int8_t byte;

//Represents a unsigned 8-bit boolean
typedef uint8_t b8;

//Represents a unsigned 16-bit boolean
typedef uint16_t b16;

//Represents a unsigned 32-bit boolean
typedef uint32_t b32;

//Represents a unsigned 64-bit boolean
typedef uint64_t b64;


//Represents a unsigned 8-bit integer
typedef uint8_t u8;

//Represents a unsigned 16-bit integer
typedef uint16_t u16;

//Represents a unsigned 32-bit integer
typedef uint32_t u32;

//Represents a unsigned 64-bit integer
typedef uint64_t u64;



//Represents a signed 8-bit integer
typedef int8_t i8;

//Represents a signed 16-bit integer
typedef int16_t i16;

//Represents a signed 32-bit integer
typedef int32_t i32;

//Represents a signed 64-bit integer
typedef int64_t i64;



//Represents a 32-bit floating point number
typedef float f32;

//Represents a 64-bit floating point number
typedef double f64;


#endif