/* net-core FUN_01034f24 @ 0x1034f24 */
#include <stdint.h>
extern void FUN_0102eb2c(int32_t, uint32_t);

uint32_t FUN_01034f24(volatile uint32_t **peripheral_ref,
                      const uint32_t *configuration)
{
    uint32_t divisor = configuration[0];
    uint32_t ratio = 1000000u / divisor;
    if (divisor * ratio != 1000000u || divisor > 1000000u ||
        (ratio & (ratio - 1)) != 0 || ratio > 0x200)
        return 0x0bad0004;

    volatile uint32_t *peripheral = *peripheral_ref;
    peripheral[0x504 / 4] =
        (peripheral[0x504 / 4] & ~3u) | (((const uint8_t *)configuration)[4] & 3u);
    peripheral[0x508 / 4] =
        (peripheral[0x508 / 4] & ~3u) | (((const uint8_t *)configuration)[5] & 3u);
    peripheral[0x510 / 4] = (uint32_t)__builtin_ctz(ratio);
    for (unsigned offset = 0x140; offset != 0x160; offset += 4) {
        *(volatile uint32_t *)((uintptr_t)peripheral + offset) = 0;
        (void)*(volatile uint32_t *)((uintptr_t)peripheral + offset);
    }
    FUN_0102eb2c(((int32_t)(uintptr_t)peripheral << 12) >> 24,
                 *(volatile uint32_t *)((uintptr_t)peripheral + 0x15c));
    return 0x0bad0000;
}
