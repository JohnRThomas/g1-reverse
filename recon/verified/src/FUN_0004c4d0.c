/* Reconstructed FUN_0004c4d0 @ 0x4c4d0, exact extent 16 bytes.
 * CFG_VERIFY_PREFIX_FIRST: hardware poweroff idle loop after observable MMIO. */
#include <stdint.h>
#include <cmsis_gcc.h>

void FUN_0004c4d0(void)
{
    *(volatile uint32_t *)0x50004500u = 1u;
    __DSB();
    for (;;)
        __WFE();
}
