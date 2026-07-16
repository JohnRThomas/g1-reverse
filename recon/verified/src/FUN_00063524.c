/* Full reconstruction of FUN_00063524 @ 0x63524 (60 bytes). */
#include <stdint.h>

uint32_t FUN_00063524(uint32_t line, uint32_t enable)
{
    uint32_t shift = line & 0xffu;

    if (enable != 0) {
        uint32_t bit = shift < 32u ? UINT32_C(1) << shift : 0;
        __atomic_fetch_or((uint32_t *)0x2000b2d8u, bit, __ATOMIC_ACQ_REL);

        uint32_t event = shift < 16u ? UINT32_C(0x10000) << shift : 0;
        *(volatile uint32_t *)0x50015304u = event;

        uint32_t pending = *(volatile uint32_t *)0x2000b2d0u;
        if (shift < 32u && ((pending >> shift) & 1u) != 0)
            *(volatile uint32_t *)0xe000e200u = UINT32_C(0x200000);
    }

    /* The leaf preserves its incoming r0 on every path. */
    return line;
}
