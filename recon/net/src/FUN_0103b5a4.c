/* net-core FUN_0103b5a4 @ 0x0103b5a4 */
#include <stdint.h>

extern void FUN_0103b62e(uint8_t *, uint32_t, uint32_t);

uint8_t *FUN_0103b5a4(uint8_t *destination, const uint8_t *source,
                     uint32_t capacity)
{
    uint8_t *out = destination;

    while (capacity != 0u) {
        uint8_t value = *source++;
        --capacity;
        *out++ = value;
        if (value == 0u) {
            break;
        }
    }
    FUN_0103b62e(out, 0u, capacity);
    return destination;
}
