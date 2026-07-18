/* FUN_0102590c @ 0x0102590c: overlap-safe private byte move. */
#include <stdint.h>
#include <stddef.h>

void *controller_memmove(void *destination, const void *source, size_t length)
{
    uint8_t *dst = destination;
    const uint8_t *src = source;
    if ((uintptr_t)(dst - src) < length) {
        while (length != 0u) {
            --length;
            dst[length] = src[length];
        }
        return destination;
    }
    if (length == 0u) {
        return destination;
    }
    if ((uintptr_t)(dst - (src + 1)) < 3u || length - 1u < 8u) {
        for (size_t i = 0; i < length; ++i) {
            dst[i] = src[i];
        }
        return destination;
    }
    size_t words_end = length & ~(size_t)3u;
    for (size_t i = 0; i < words_end; i += 4u) {
        uint32_t word = *(const uint32_t *)(src + i);
        *(uint32_t *)(dst + i) = word;
    }
    for (size_t i = words_end; i < length; ++i) {
        dst[i] = src[i];
    }
    return destination;
}

/* Raw identity/back-map: FUN_0102590c @ 0x0102590c, true extent 0x8a. */
extern __typeof(controller_memmove) FUN_0102590c
    __attribute__((alias("controller_memmove")));
