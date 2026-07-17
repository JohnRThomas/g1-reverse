/* net-core FUN_0100e83c @ 0x100e83c  (CFG-directed candidate) */
/* net-core FUN_0100e83c @ 0x0100e83c
 * Readable role: copy a 34-byte controller descriptor and its trailing 8-byte timing pair.
 */
#include <stdint.h>

void FUN_0100e83c(void *destination, const void *descriptor,
                  const void *timing_pair)
{
    uint8_t *dst = (uint8_t *)destination + 4;
    const uint32_t *src_words = (const uint32_t *)descriptor;
    uint32_t *dst_words = (uint32_t *)dst;
    unsigned int i;

    for (i = 0; i < 8; ++i) {
        dst_words[i] = src_words[i];
    }
    *(uint16_t *)(dst + 32) = *(const uint16_t *)((const uint8_t *)descriptor + 32);
    *(uint32_t *)((uint8_t *)destination + 0x26) =
        *(const uint32_t *)timing_pair;
    *(uint32_t *)((uint8_t *)destination + 0x2a) =
        *(const uint32_t *)((const uint8_t *)timing_pair + 4);
}
