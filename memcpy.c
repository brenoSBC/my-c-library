#include <stdio.h>
#include <stdint.h>

/*

memcpy, specifically designed for 64-bit systems where sizeof(size_t) == 8.

*/

#define PREFETCH_THRESHOLD 1024
#define PREFETCH_DISTANCE 256

#define UNALIGNED(dest, src)                    \
    ((uintptr_t)(dest) % sizeof(size_t) != 0 || \
     (uintptr_t)(src) % sizeof(size_t) != 0)

void *my_memcpy(void *dest, const void *src, size_t n)
{

    unsigned char *pdest = dest;
    const unsigned char *psrc = src;

    unsigned char *ptr = dest;

    while (n > 0 && UNALIGNED(pdest, psrc))
    {
        *pdest = *psrc;
        ++pdest;
        ++psrc;
        --n;
    }

    if (n >= PREFETCH_THRESHOLD)
    {
        while (n >= sizeof(size_t))
        {
            /*
            __builtin_prefetch(psrc + 256, 0, 3):

                PREFETCH_DISTANCE = +256 : prefetch 4 cache lines ahead
                (64 bytes per cache line)

                0 : read access (operation is read, not written)

                3 : high temporal locality; keep data in cache as long as possible
            */
            __builtin_prefetch(psrc + PREFETCH_DISTANCE, 0, 3);

            *(size_t *)pdest = *(const size_t *)psrc;
            pdest += sizeof(size_t);
            psrc += sizeof(size_t);
            n -= sizeof(size_t);
        }
    }
    else
    {
        while (n >= sizeof(size_t))
        {
            *(size_t *)pdest = *(const size_t *)psrc;
            pdest += sizeof(size_t);
            psrc += sizeof(size_t);
            n -= sizeof(size_t);
        }
    }

    while (n != 0)
    {
        *pdest = *psrc;
        ++pdest;
        ++psrc;
        --n;
    }

    return ptr;
}