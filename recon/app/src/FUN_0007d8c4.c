/* Reconstructed FUN_0007d8c4 @ 0x7d8c4. */
#include <stdint.h>

/* Assemble little-endian input bytes into aligned destination words. */
void FUN_0007d8c4(uint32_t *dst, const uint8_t *src, uint32_t byte_count)
{
    uint32_t offset = 0;

    while (offset < byte_count) {
        uint32_t word = (uint32_t)src[offset]
                      | (uint32_t)src[offset + 1] << 8
                      | (uint32_t)src[offset + 2] << 16
                      | (uint32_t)src[offset + 3] << 24;
        dst[offset / 4] = word;
        offset += 4;
    }
}
