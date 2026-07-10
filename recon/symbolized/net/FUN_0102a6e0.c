#include "g1_net_symbols.h"
/* net-core FUN_0102a6e0 @ 0x102a6e0  (parity 300 trials PROVEN) */

extern void FUN_0103b614(void *dst, void *src, unsigned int n);
extern int FUN_010362d0(unsigned int a, void *b, int c, int d);

int FUN_0102a6e0(void *param_1)
{
    unsigned char buf[256];
    int iVar1;
    FUN_0103b614(buf, (void*)"ong Command payload lenh\n" /*=0x103c798*/, 0xfb);
    if (*(volatile int *)(((uintptr_t)&g_zephyr_log_backend_ctx) /*=0x210045b0*/ + 0x10) == 0) {
        iVar1 = 1;
    } else {
        iVar1 = FUN_010362d0(((uintptr_t)&g_zephyr_log_backend_ctx) /*=0x210045b0*/, buf, 0, 0);
        if (iVar1 == 0) {
            FUN_0103b614(param_1, buf, 0xfb);
        }
    }
    return iVar1;
}

