/* net-core FUN_01024aa8 @ 0x1024aa8  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

void FUN_01024aa8(void)
{
    volatile unsigned int * const p = (volatile unsigned int * const)G1_NRF_CLOCK_NS_BASE;
    volatile unsigned char * const q = (volatile unsigned char * const)0x21001bf7;
    p[1] = 1;
    p[0x40] = 0;
    q[0] = 0;
}

