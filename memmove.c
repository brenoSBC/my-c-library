#include <stdio.h>
#include <stdint.h>

void *my_memmove(void *dest, void *src, int n)
{

    unsigned char *pdest = (char *)dest;
    const unsigned char *psrc = (char *)src;

    if ((uintptr_t)pdest > (uintptr_t)psrc && (uintptr_t)pdest < (uintptr_t)psrc + n)
    {

    }
    else
    {

    }

    return dest;
}
