/* net-core FUN_01020108 @ 0x1020108  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"

extern uint32_t FUN_01008d00(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);
extern int32_t FUN_01023ac4(void);

void FUN_01020108(void)
{
    volatile uint8_t * const flagbyte = (uint8_t *)0x210015f0;
    uint8_t r3 = flagbyte[0x35];

    if ((r3 & 1) == 0) {
        return;
    }

    if (r3 & 2) {
        volatile uint32_t *base = (uint32_t *)G1_NRF_RADIO_NS_BASE;
        uint32_t uVar2 = *(volatile uint32_t *)((uint8_t *)base + 0x200) | 1;
        *(volatile uint32_t *)((uint8_t *)base + 0x200) = uVar2;
        uint32_t f = *(volatile uint32_t *)((uint8_t *)base + 0x550);
        if ((f & 0xf6) == 2) {
            FUN_01008d00(0x3e, 0x5a7, uVar2, 2, 0);
            /* falls through to the bit-2 test, matching original layout */
        }
    }

    if (r3 & 4) {
        volatile uint32_t *base2 = (uint32_t *)G1_NRF_RADIO_NS_BASE;
        *(volatile uint32_t *)((uint8_t *)base2 + 0x88) = 0x80000008;
        int32_t iVar1 = FUN_01023ac4();
        if (iVar1 != 0) {
            FUN_01008d00(0x3e, 0x5af, 0, 0, 0);
            for (;;) {}
        }
    }
}

