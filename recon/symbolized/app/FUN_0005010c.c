#include "g1_app_symbols.h"
/* named: FUN_0005010c */
/* Reconstructed FUN_0005010c @ 0x5010c  (parity: 300/300 trials, PROVEN) */

extern int printk(int a, int b, int c, int d, int e);
extern int assert_post_action(int a, int b);

void FUN_0005010c(int param_1, unsigned int param_2, int param_3, int param_4)
{
    int r0 = param_1;
    int r2 = param_3;
    int r3 = (int)(param_2 + 1U);
    signed char cVar1;
    int bVar5;

    if ((unsigned int)r3 > 7) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "prio <= ((1UL << (3)) - 1)" /*=0xf1bde*/, "WEST_TOPDIR/zephyr/arch/arm/core/aarch32/irq_manage.c" /*=0xf1ba8*/, 0x5c, param_4);
        r3 = 7;
        r2 = param_1;
        printk("\tinvalid priority %d for %d irq! values must be less than %lu\n\n" /*=0xf1bf9*/, (int)param_2, r2, r3, 0);
        r0 = assert_post_action("WEST_TOPDIR/zephyr/arch/arm/core/aarch32/irq_manage.c" /*=0xf1ba8*/, 0x5c);
    }
    r0 = (int)(signed char)r0;
    bVar5 = (r0 >= 0);
    if (bVar5) {
        r0 = r0 + (int)0xe0000000;
    } else {
        r2 = (int)0xe000ed14;
    }
    r3 = r3 << 5;
    r3 = (unsigned char)r3;
    if (bVar5) {
        r0 = r0 + ((uintptr_t)&rodata_e100) /*=0xe100*/;
        cVar1 = (signed char)r3;
        *(char *)(r0 + 0x300) = cVar1;
    } else {
        r0 = r0 & 0xf;
        cVar1 = (signed char)r3;
        *(char *)(r2 + r0) = cVar1;
    }
}

