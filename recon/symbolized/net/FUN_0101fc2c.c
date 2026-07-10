#include "g1_net_symbols.h"
/* net-core FUN_0101fc2c @ 0x101fc2c  (parity 300 trials PROVEN) */

void FUN_0101fc2c(void)
{
    volatile unsigned char * const p = (volatile unsigned char * const)((uintptr_t)&g_net_ccm_op_status) /*=0x210014d8*/;
    p[0] = 0;
    *(volatile unsigned short *)(p + 1) = 0x1000;
}

