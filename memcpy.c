#include <stdio.h>
#include <stdint.h>

/*

memcpy, specifically designed for 64-bit systems where sizeof(size_t) == 8.

*/

#define UNALIGNED(dest, src) \
    ((uintptr_t)(dest) % sizeof(size_t) != 0 || \
     (uintptr_t)(src)  % sizeof(size_t) != 0)

void *my_memcpy(void *dest, const void *src, size_t n) {

    unsigned char *pdest = dest;
    const unsigned char *psrc = src;

    unsigned char *ptr = dest;

    while(n > 0 && UNALIGNED(pdest, psrc)) {
        *pdest = *psrc;
        ++pdest;
        ++psrc;
        --n;      
    }

    while(n >= sizeof(size_t)) {
        *(size_t *)pdest = *(const size_t *)psrc;
        pdest+=sizeof(size_t);
        psrc+=sizeof(size_t);
        n-=sizeof(size_t);
    }

    while(n != 0) {
        *pdest = *psrc;
        ++pdest;
        ++psrc;
        --n;      
    }

    return ptr;
}