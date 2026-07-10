#include "g1_net_symbols.h"
/* net-core FUN_0102fcc4 @ 0x102fcc4  (parity 300 trials PROVEN) */

extern void FUN_0102ff54(unsigned int, unsigned int, unsigned int, unsigned int);
unsigned int FUN_0102fcc4(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile unsigned int * const p = (volatile unsigned int * const)((uintptr_t)&g_net_047fc) /*=0x210047fc*/;
    FUN_0102ff54(*p, param_1, param_3, (unsigned int)p);
    return 0;
}

