#include <stdio.h>
#include <stdint.h>

int my_memcmp(const void *s1, const void *s2, size_t n) {

    unsigned char *ps1 = s1;
    unsigned char *ps2 = s2;

    while(n != 0) {
        if(*ps1 != *ps2) {
            return ps1 - ps2;
        }
        ++ps1;
        ++ps2;
        --n;
    }
    return 0;
}