/* CPUNET controller slot allocation @ 0x01022e34.
 * Raw back-map: FUN_01022e34@0x01022e34; extent 0x50. */
#include <stdint.h>

extern void FUN_010248d0(void);

unsigned FUN_01022e34(uint32_t first, uint32_t second)
{
    volatile uint8_t *const table = (volatile uint8_t *)0x210016f0u;
    unsigned bank;
    unsigned slot;

    FUN_010248d0();
    bank = table[0x49];
    for (slot = 0; slot != 0x20; ++slot) {
        if (table[0x50 + bank * 0x40 + slot * 2] == 0) {
            *(volatile uint32_t *)(table + 0xd0 + slot * 0x20) = first;
            *(volatile uint32_t *)(table + 0xd4 + slot * 0x20) = second;
            table[0x50 + (slot + bank * 0x20) * 2] = 1;
            return (uint8_t)slot;
        }
    }
    return 0x20;
}
