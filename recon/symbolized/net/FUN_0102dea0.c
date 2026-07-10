#include "g1_net_symbols.h"
/* net-core FUN_0102dea0 @ 0x102dea0  (parity 300 trials PROVEN) */

extern void FUN_0102cbd8(unsigned int, unsigned int);
void FUN_0102dea0(void)
{
    unsigned int uVar1 = ((uintptr_t)&g_net_periodic_work_obj) /*=0x2100086c*/;
    volatile unsigned int * const p = (volatile unsigned int * const)((uintptr_t)&g_net_periodic_work_ptr) /*=0x2100465c*/;
    FUN_0102cbd8(uVar1, ": %s\n" /*=0x103c900*/);
    *p = uVar1;
}

