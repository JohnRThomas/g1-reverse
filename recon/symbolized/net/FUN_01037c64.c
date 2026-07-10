#include "g1_net_symbols.h"
/* net-core FUN_01037c64 @ 0x1037c64  (parity 300 trials PROVEN) */
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int, unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01037768(unsigned int);
extern int FUN_01037b5c(void);

unsigned int FUN_01037c64(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int ipsr;
    __asm__ volatile("mrs %0, ipsr" : "=r"(ipsr));
    if (ipsr != 0) {
        FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103eb0e) /*=0x103eb0e*/, 0x5c1, ipsr);
        FUN_01039bb0(((uintptr_t)&rodata_103eb0e) /*=0x103eb0e*/, 0x5c1);
    }
    unsigned int uVar3;
    if (param_2 == -1 && param_1 == -1) {
        volatile unsigned int * const dat = (volatile unsigned int *)((uintptr_t)&g_zephyr_kernel_readyq) /*=0x21004b28*/;
        FUN_01037768(*(unsigned int*)((char*)dat + 8));
        uVar3 = 0xffffffff;
    } else {
        int iVar2 = FUN_01037b5c();
        long long prod = (long long)iVar2 * 1000;
        uVar3 = (unsigned int)(((unsigned long long)prod) >> 0xf) |
                ((unsigned int)(((unsigned long long)prod) >> 0x20) << 0x11);
    }
    return uVar3;
}

