#include "g1_net_symbols.h"
/* net-core FUN_01037130 @ 0x1037130  (parity 300 trials PROVEN) */
extern int FUN_01036128(int a);
extern void FUN_0102ec10(int a);
extern void FUN_01039bb0(int a, int b);
extern void FUN_01039bbe(int a, int b, int c);

static inline unsigned int read_ipsr(void)
{
    unsigned int v;
    __asm__ volatile("mrs %0, ipsr" : "=r"(v));
    return v;
}

static inline void write_basepri(unsigned int v)
{
    __asm__ volatile("msr basepri, %0" : : "r"(v));
}

static inline void isb_sy(void)
{
    __asm__ volatile("isb sy");
}

void FUN_01037130(unsigned int param_1, unsigned int param_2)
{
    unsigned int r5 = 0;
    int r1val;

    if (param_2 == 0) {
        r5 = read_ipsr();
        if (r5 == 0) {
            unsigned int *base = (unsigned int *)((uintptr_t)&g_zephyr_kernel_readyq) /*=0x21004b28*/;
            unsigned int a = *(volatile unsigned int *)((char *)base + 0x14);
            unsigned int b = *(volatile unsigned int *)((char *)base + 8);
            if (a != b) {
                int iVar2 = FUN_01036128((int)param_1);
                if (iVar2 != 0) {
                    FUN_0102ec10((int)r5);
                    return;
                }
                FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, "***** HARD FAULT *****" /*=0x103d3b6*/, 0x111);
                r1val = 0x111;
                FUN_01039bb0("***** HARD FAULT *****" /*=0x103d3b6*/, r1val);
                FUN_0102ec10((int)r5);
                return;
            }
        }
    }

    int iVar2b = FUN_01036128((int)param_1);
    if (iVar2b != 0) {
        write_basepri(param_2);
        isb_sy();
        return;
    }
    FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, "***** HARD FAULT *****" /*=0x103d3b6*/, 0xf0);
    r1val = 0xf0;
    FUN_01039bb0("***** HARD FAULT *****" /*=0x103d3b6*/, r1val);
    FUN_0102ec10((int)r5);
}


