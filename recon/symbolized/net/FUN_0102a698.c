#include "g1_net_symbols.h"
/* net-core FUN_0102a698 @ 0x102a698  (parity 300 trials PROVEN) */

extern void FUN_0103b614(void *dst, void *src, unsigned int n);
extern int FUN_01036198(unsigned int a, void *b, int c, int d);
extern void FUN_01039722(unsigned int a);

int FUN_0102a698(void *param_1)
{
    unsigned char buf[256];
    int iVar1;
    if (*(volatile int*)(0x210045b0 + 0x10) == 0) {
        iVar1 = 1;
    } else {
        FUN_0103b614(buf, param_1, 0xfb);
        iVar1 = FUN_01036198(0x210045b0, buf, 0, 0);
        if (iVar1 != 0 && 0 < *(volatile int*)((unsigned long)&g_zephyr_log_level) /*=0x21000580*/) {
            FUN_01039722(((unsigned long)&rodata_103cd46) /*=0x103cd46*/);
        }
    }
    return iVar1;
}
