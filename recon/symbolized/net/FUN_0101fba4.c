#include "g1_net_symbols.h"
/* net-core FUN_0101fba4 @ 0x101fba4  (parity 300 trials PROVEN) */

unsigned int FUN_0101fba4(void)
{
    volatile unsigned char * const p = (volatile unsigned char * const)((uintptr_t)&g_net_link_mode_ctx) /*=0x21001498*/;
    if (p[0x10] == 0) return 0x138;
    return 0x214;
}

