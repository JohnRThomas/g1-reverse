/* net-core FUN_01025998 @ 0x01025998
 * Alignment-aware non-overlapping byte copy used by MPSL.
 */
#include <stdint.h>

void FUN_01025998(void *destination, const void *source, uint32_t length)
{
    volatile uint8_t *dst8 = (volatile uint8_t *)destination;
    const volatile uint8_t *src8 = (const volatile uint8_t *)source;

    if ((((uintptr_t)dst8 ^ (uintptr_t)src8) & 3u) == 0u) {
        while ((((uintptr_t)dst8 & 3u) != 0u) && length != 0u) {
            *dst8++ = *src8++;
            length--;
        }
        if (length > 3u) {
            uint32_t words = length >> 2;
            volatile uint32_t *dst32 = (volatile uint32_t *)(void *)dst8;
            const volatile uint32_t *src32 =
                (const volatile uint32_t *)(const void *)src8;
            uint32_t index = 0u;
            while (index < words) {
                dst32[index] = src32[index];
                index++;
            }
            dst8 += words * 4u;
            src8 += words * 4u;
            length &= 3u;
        }
    } else if (length > 3u) {
        uint32_t words = length >> 2;
        uint32_t index = 0u;
        while (index < words) {
            uint32_t value;
            __builtin_memcpy(&value, (const void *)(src8 + index * 4u), 4u);
            __builtin_memcpy((void *)(dst8 + index * 4u), &value, 4u);
            index++;
        }
        dst8 += words * 4u;
        src8 += words * 4u;
        length &= 3u;
    }

    if (length != 0u) {
        dst8[0] = src8[0];
        if (length != 1u) {
            dst8[1] = src8[1];
            if (length != 2u) {
                dst8[2] = src8[2];
            }
        }
    }
}
