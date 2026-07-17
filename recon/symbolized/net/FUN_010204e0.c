#include "g1_net_symbols.h"
/* net-core FUN_010204e0 @ 0x10204e0  (parity 300 trials PROVEN) */

void FUN_010204e0(unsigned int param_1)
{
    volatile unsigned int * const p = (volatile unsigned int * const)REG_41008000 /*=0x41008000*/;
    *(volatile unsigned int *)((char*)p + 0x524) = param_1 >> 0x18;
    *(volatile unsigned int *)((char*)p + 0x51c) = param_1 << 8;
}
