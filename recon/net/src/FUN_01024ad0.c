/* net-core FUN_01024ad0 @ 0x1024ad0  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

#define DAT_01024ae8 ((unsigned int)G1_NRF_CLOCK_NS_BASE)
#define DAT_01024aec ((volatile unsigned char *)0x21001bf7)

unsigned char FUN_01024ad0(void)
{
    unsigned char bVar1;
    if (*(volatile int *)(DAT_01024ae8 + 0x100) == 0) {
        bVar1 = *DAT_01024aec;
    } else {
        bVar1 = 1;
    }
    return bVar1 & 1;
}

