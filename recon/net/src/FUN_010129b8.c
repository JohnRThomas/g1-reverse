/* net-core FUN_010129b8 @ 0x10129b8  (CFG-directed candidate) */

#include <stdint.h>
extern void sdc_assertion_fail(uint32_t, uint32_t, uint32_t, uint32_t) __asm__("FUN_01008d00");
void FUN_010129b8(uint8_t *shape, uint32_t width, uint32_t height, uint32_t unused)
{
    uint32_t flags = shape[2];
    shape[0] = (uint8_t)width;
    shape[1] = (uint8_t)height;
    uint32_t dimensions = ((flags >> 2) & 1u) + ((flags >> 1) & 1u) + (flags & 1u);
    uint32_t total = dimensions * width * height;
    if ((int32_t)total > 0xfe)
        sdc_assertion_fail(0x2e, 0x5c, total, dimensions);
}
