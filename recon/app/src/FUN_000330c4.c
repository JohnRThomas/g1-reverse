/* ABI-faithful reconstruction of FUN_000330c4 @ 0x330c4 (16 bytes). */
#include <stdint.h>

extern void FUN_0007c8b0(uint32_t enabled, uint32_t inherited_r1,
                         uint32_t inherited_r2, uint32_t inherited_r3);

uint32_t FUN_000330c4(uint32_t ignored, uint32_t inherited_r1,
                      uint32_t inherited_r2, uint32_t inherited_r3)
{
    (void)ignored;
    uint32_t enabled = *(volatile uint32_t *)0x20002424u;
    if (enabled != 0)
        FUN_0007c8b0(enabled, inherited_r1, inherited_r2, 0x20002424u);
    return 0;
}
