#include "g1_net_symbols.h"
/* net-core FUN_01025be0 @ 0x1025be0  (parity 300 trials PROVEN) */

int FUN_01025be0(void)
{
    volatile int * const p = (volatile int * const)((uintptr_t)&g_net_driver_api_ptr) /*=0x21000574*/;
    int iVar1 = *p - 0x103c780 /*=0x103c780*/;
    if (iVar1 != 0) iVar1 = 1;
    return iVar1;
}

