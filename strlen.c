#include <stdio.h>
#include <stdint.h>

/*

strlen, specifically designed for 64-bit systems where sizeof(size_t) == 8.

*/

size_t my_strlen(const char *string)
{
    const char *start = string;

    while ((uintptr_t)string % sizeof(size_t) != 0)
    {
        if (*string == '\0')
        {
            return (size_t)(string - start);
        }
        ++string;
    }

    const size_t *w = (size_t *)string;

    for (;;)
    {
        size_t value = *w;
        if (((value - 0x0101010101010101ULL) & ~value & 0x8080808080808080ULL) != 0)
        {
            break;
        }
        ++w;
    }

    const char *c = (const char *)w;
    while (*c != '\0')
    {
        ++c;
    }

    return (size_t)(c - start);
}
