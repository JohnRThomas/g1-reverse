#include "g1_app_symbols.h"
/* named: lock_acquire_or_fatal */
/* Reconstructed lock_acquire_or_fatal @ 0x510fc  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(int,int);
extern void printk(int,int,int,int);
extern void k_mutex_lock(int,int,int,int);
void lock_acquire_or_fatal(int param_1, int param_2)
{
    if (param_1 == 0) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "lock != ((void *)0)" /*=0xf23d4*/, "WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c" /*=0xf22d5*/, 0x1a6);
        assert_post_action("WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c" /*=0xf22d5*/, 0x1a6);
    }
    k_mutex_lock(param_1, param_2, -1, -1);
}

