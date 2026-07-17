#include "g1_net_symbols.h"
/* net-core FUN_0100a5a0 @ 0x100a5a0  (parity 300 trials PROVEN) */

int FUN_0100a5a0(void)
{
    volatile int * const p = (volatile int * const)((unsigned long)&g_net_retry_handle) /*=0x21000bc4*/;
    return *p;
}
