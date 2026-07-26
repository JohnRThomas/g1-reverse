/* net-core FUN_01024b20 @ 0x1024b20  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

unsigned int FUN_01024b20(unsigned char param_1)
{
    volatile unsigned int *base = (volatile unsigned int *)G1_NRF_CLOCK_NS_BASE;
    unsigned int a = base[0x418/4];
    unsigned int b = base[0x418/4];
    unsigned int uVar1 = a & 0x10000;
    if (uVar1 != 0) {
        uVar1 = (unsigned int)((b & 3) == (unsigned int)param_1);
    }
    return uVar1;
}

