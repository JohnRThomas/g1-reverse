/* net-core FUN_0103499c @ 0x103499c  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

extern void FUN_0103b62e(void*, int, int);
extern unsigned int FUN_01034650(unsigned int);
extern void arch_irq_enable(int); /* FUN_0102eb2c */

unsigned int FUN_0103499c(void)
{
    volatile unsigned char *base = (volatile unsigned char*)0x210006a8;
    if (base[0x78] != 0) {
        return 0x0bad0005;
    }
    FUN_0103b62e((void*)(base + 0x10), 0, 0x60);
    unsigned int uVar4;
    for (uVar4 = 0; uVar4 != 8; uVar4++) {
        unsigned int r0 = FUN_01034650(uVar4 & 0xff);
        if (((r0 - 0x100u) >> 2) == 0x1f) {
            volatile unsigned int *channel =
                (volatile unsigned int*)(r0 + G1_NRF_GPIOTE_NS_BASE); /* raw computed MMIO back-map */
            *channel = 0;
            (void)*channel; /* conditional read-back, original 0x010349d4 */
        }
    }
    volatile unsigned char *e4 = (volatile unsigned char*)G1_NRF_GPIOTE_NS_BASE;
    *(volatile unsigned int*)(e4 + 0x17c) = 0;
    (void)*(volatile unsigned int*)(e4 + 0x17c); /* read-back @ 0x4100a17c, raw 0x010349e4 */
    arch_irq_enable(10);
    *(volatile unsigned int*)(e4 + 0x304) = 0x80000000;
    base[0x78] = 1;
    *(volatile unsigned int*)(base + 0x74) = 1;
    return 0x0bad0000;
}
