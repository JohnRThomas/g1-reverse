#include "g1_app_symbols.h"
/* named: z_abort_thread_timeout */
/* Reconstructed z_abort_thread_timeout @ 0x74274  (parity: 300/300 trials, PROVEN) */

extern void dlist_unlink_node(int, int);
extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned long long assert_post_action(unsigned int, unsigned int);

void z_abort_thread_timeout(int param_1)
{
    int v8 = *(volatile int*)(param_1 + 8);
    int r0;
    if (v8 == 0) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "thread->base.pended_on" /*=0xf85bb*/, "WEST_TOPDIR/zephyr/kernel/sched.c" /*=0xf82f4*/, 0x2d2UL);
        unsigned long long rv = assert_post_action("WEST_TOPDIR/zephyr/kernel/sched.c" /*=0xf82f4*/, 0x2d2UL);
        r0 = (int)rv;
    } else {
        r0 = v8;
    }
    dlist_unlink_node(r0, param_1);
    unsigned char b = *(volatile unsigned char*)(param_1 + 0xd);
    *(volatile unsigned char*)(param_1 + 0xd) = b & 0xfd;
    *(volatile int*)(param_1 + 8) = 0;
}

