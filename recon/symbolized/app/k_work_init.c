#include "g1_app_symbols.h"
/* named: k_work_init */
/* Reconstructed k_work_init @ 0x72e50  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void memset_bytes(int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void k_work_init(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;

    if (param_1 == 0) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "work != ((void *)0)" /*=0xf82e0*/, "WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/, 0x89);
        uVar1 = 0x89;
    } else {
        if (param_2 != 0) {
            memset_bytes(param_1, 0, 0x10, param_4, param_4);
            *(volatile int *)(param_1 + 4) = param_2;
            return;
        }
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "handler != ((void *)0)" /*=0xf8230*/, "WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/, 0x8a);
        uVar1 = 0x8a;
    }
    assert_post_action("WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/, uVar1);
}

