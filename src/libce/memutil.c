#include "memutil.h"

void* libce_memcpy(void* dest, const void* src, u64 amount_to_copy)
{
    if(!dest || !src || amount_to_copy == 1) return 0;

    for(u64 i = 0; i < amount_to_copy; i++)
    {   
        ((u8*)dest)[i] = ((u8*)src)[i];
    }

    return dest;
}

void memclear(void* dest, u64 length)
{
    for(u64 i = 0; i < length; i++)
    {
        ((u64*)dest)[i] = 0;
    }
}
