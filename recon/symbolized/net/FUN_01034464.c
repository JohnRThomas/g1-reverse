#include "g1_net_symbols.h"
/* net-core FUN_01034464 @ 0x1034464  (parity 300 trials PROVEN) */

extern void FUN_01034368(unsigned int, unsigned int);
void FUN_01034464(unsigned int param_1)
{
    volatile unsigned int * const p = (volatile unsigned int * const)REG_4100f000 /*=0x4100f000*/;
    p[0x142] = 1u << (param_1 & 0xff);
    FUN_01034368(((uintptr_t)&g_sdc_res_pool_free_bitmap) /*=0x210006a4*/, param_1);
}

