#include "g1_net_symbols.h"
/* net-core FUN_01036f24 @ 0x1036f24  (parity 300 trials PROVEN) */

extern void FUN_010380d8(unsigned int a);
extern int FUN_01036e90(unsigned int a);
extern void FUN_01037f8c(unsigned int a, unsigned int b, int lo, int hi);

void FUN_01036f24(unsigned int param_1)
{
    unsigned char bVar1 = *(volatile unsigned char *)(((uintptr_t)&g_zephyr_kernel_readyq) /*=0x21004b28*/ + 0x10);
    unsigned int iVar3 = (unsigned int)bVar1 * 0x18 + ((uintptr_t)&g_net_ctx_record_tbl) /*=0x210044d8*/;
    int iVar2;
    int v;
    FUN_010380d8(iVar3);
    *(volatile unsigned char *)(((uintptr_t)&g_net_ctx_busy_flags) /*=0x21006462*/ + bVar1) = 0;
    iVar2 = FUN_01036e90(param_1);
    if (iVar2 != 0) {
        v = *(volatile int *)((uintptr_t)&g_net_ctx_active_count) /*=0x21004b64*/ - 1;
        FUN_01037f8c(iVar3, ((uintptr_t)&rodata_10376cd) /*=0x10376cd*/, v, v >> 0x1f);
    }
}

