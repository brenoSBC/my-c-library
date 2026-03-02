#include <stdio.h>
#include <stdint.h>

int my_memcmp(const void *s1, const void *s2, size_t n) {

    const unsigned char *ps1 = s1;
    const unsigned char *ps2 = s2;

    while(n > 0 && (uintptr_t)ps1 % sizeof(size_t) != 0 || (uintptr_t)ps2 % sizeof(size_t)) {
        if(*ps1 != *ps2) {
            return *ps1 - *ps2;
        }
        ++ps1;
        ++ps2;
        --n;
    }

    while(n >= sizeof(size_t)) {
        if(*(size_t *)ps1 != *(size_t *)ps2) {
            break;
        }
        ps1 += sizeof(size_t);
        ps2 += sizeof(size_t);
        n   -= sizeof(size_t);
    }

    while(n != 0) {
        if(*ps1 != *ps2) {
            return *ps1 - *ps2;
        }
        ++ps1;
        ++ps2;
        --n;
    }
    return 0;
}
