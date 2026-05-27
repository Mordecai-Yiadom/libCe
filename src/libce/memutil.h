#ifndef LIBCE_MEMUTIL_H
#define LIBCE_MEMUTIL_H

#include "memtypes.h"


/*
    Copies bytes from one address to another.
    
    @param
    dest the address to copy the data to.

    @param
    src the addreess to copy the data from.

    @param
    amount_to_copy the amount of bytes to copy from the 'src' address

    @return
    Returns the 'dest' address if bytes have been successfully written or NULL if writing failed.
*/
void* libce_memcpy(void* dest, const void* src, u64 amount_to_copy);


void memclear(void* dest, u64 length);


#endif