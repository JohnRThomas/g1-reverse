#include "g1_net_symbols.h"
/* net-core FUN_0101f894 @ 0x101f894  (parity 300 trials PROVEN) */

#define DAT_0101f8ac ((unsigned int)((unsigned long)&g_net_flags_bitmap64) /*=0x21000020*/)

void FUN_0101f894(unsigned int param_1)
{
    unsigned int idx = param_1 >> 3;
    unsigned char bit = (unsigned char)(1 << (param_1 & 7));
    *(volatile unsigned char *)(DAT_0101f8ac + idx) = bit | *(volatile unsigned char *)(DAT_0101f8ac + idx);
    return;
}
