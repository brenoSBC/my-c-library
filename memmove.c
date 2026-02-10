#include <stdio.h>
#include <stdint.h>

void *my_memmove(void *dest, const void *src, size_t n)
{

    if(dest == src || n == 0) {
        return dest;
    }

    unsigned char *pdest = dest;
    const unsigned char *psrc = src;

    if ((uintptr_t)pdest > (uintptr_t)psrc && (uintptr_t)pdest < (uintptr_t)psrc + n)
    {
        unsigned char *last_dest = pdest + (n - 1);
        unsigned char *last_src = psrc + (n - 1);

        while(n != 0) {
            *last_dest = *last_src;
            --last_dest;
            --last_src;
            --n;
        }
    }
    else
    {
        while(n != 0) {
            *pdest = *psrc;
            ++pdest;
            ++psrc;
            --n;
        }
    }

    return dest;
}
