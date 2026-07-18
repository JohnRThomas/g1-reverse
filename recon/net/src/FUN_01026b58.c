/* net-core FUN_01026b58 @ 0x1026b58  (CFG-directed candidate) */

#include <stdint.h>
extern int32_t FUN_01026912(uint16_t, uint16_t);
uintptr_t FUN_01026b58(uint8_t *context, uint16_t *limit, uint8_t *is_empty)
{
    uint16_t flags = *(uint16_t *)(context + 4);
    uint16_t offset = flags & 0x7fffu;
    if (FUN_01026912(flags, *(uint16_t *)(context + 6)) != 0) {
        *(uint16_t *)(context + 0x0e) = 0;
        return 0;
    }
    uint8_t *item = context + 0x18 + offset;
    uint16_t available = (uint16_t)(*(uint16_t *)item - *(uint16_t *)(context + 0x0a));
    if (available < *limit)
        *limit = available;
    *is_empty = *(uint16_t *)(context + 0x0a) == 0;
    *(uint16_t *)(context + 0x0e) = *limit;
    return (uintptr_t)(item + context[0x13] + *(uint16_t *)(context + 0x0a) + 2);
}
