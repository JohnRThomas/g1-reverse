/* Reconstructed FUN_0008705a @ 0x8705a. */
#include <stdint.h>

/* Bounded string copy with zero-fill, matching strncpy semantics. */
void FUN_0008705a(char *dst, const char *src, uint32_t count)
{
    while (count != 0) {
        char ch = *src++;
        --count;
        *dst++ = ch;
        if (ch == '\0')
            break;
    }

    while (count != 0) {
        *dst++ = '\0';
        --count;
    }
}
