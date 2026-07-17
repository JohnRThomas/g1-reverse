#include "g1_net_symbols.h"
/* net-core FUN_0102bba8 @ 0x102bba8  (parity 300 trials PROVEN) */

extern void FUN_0102b900(unsigned int);
#define DAT_0102bbc0 ((volatile unsigned int *)((unsigned long)&g_net_evt_callback_fn) /*=0x2100463c*/)

void FUN_0102bba8(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    *DAT_0102bbc0 = param_1;
    FUN_0102b900(0);
    FUN_0102b900(1);
    return;
}
