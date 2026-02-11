#include <stdio.h>
#include <stdint.h>

#define UNALIGNED(dest, src)                    \
    ((uintptr_t)(dest) % sizeof(size_t) != 0 || \
     (uintptr_t)(src) % sizeof(size_t) != 0)

void *my_memmove(void *dest, const void *src, size_t n)
{

    if (dest == src || n == 0)
    {
        return dest;
    }

    unsigned char *pdest = dest;
    const unsigned char *psrc = src;

    if ((uintptr_t)pdest > (uintptr_t)psrc && (uintptr_t)pdest < (uintptr_t)psrc + n)
    {
        unsigned char *last_dest = pdest + (n - 1);
        unsigned char *last_src = psrc + (n - 1);

        while (n > 0 && UNALIGNED(last_dest, last_src))
        {
            *last_dest = *last_src;
            --last_dest;
            --last_src;
            --n;
        }

        while (n >= sizeof(size_t))
        {
            *(size_t *)(last_dest - sizeof(size_t) + 1) = *(const size_t *)(last_src - sizeof(size_t) + 1);
            last_dest -= sizeof(size_t);
            last_src -= sizeof(size_t);
            n -= sizeof(size_t);
        }

        while (n != 0)
        {
            *last_dest = *last_src;
            --last_dest;
            --last_src;
            --n;
        }
    }
    else
    {
        while (n > 0 && UNALIGNED(pdest, psrc))
        {
            *pdest = *psrc;
            ++pdest;
            ++psrc;
            --n;
        }

        while (n >= sizeof(size_t))
        {
            *(size_t *)pdest = *(const size_t *)psrc;
            pdest += sizeof(size_t);
            psrc += sizeof(size_t);
            n -= sizeof(size_t);
        }

        while (n != 0)
        {
            *pdest = *psrc;
            ++pdest;
            ++psrc;
            --n;
        }
    }

    return dest;
}
