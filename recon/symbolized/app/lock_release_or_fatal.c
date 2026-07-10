#include "g1_app_symbols.h"
/* named: lock_release_or_fatal */
/* Reconstructed lock_release_or_fatal @ 0x51134  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern void assert_post_action(int a, int b);
extern void k_mutex_unlock(void);
void lock_release_or_fatal(int param_1, int param_2, int param_3, int param_4)
{
  if (param_1 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "lock != ((void *)0)" /*=0xf23d4*/, "WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c" /*=0xf22d5*/, 0x1c2, param_4);
    assert_post_action("WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c" /*=0xf22d5*/, 0x1c2);
  }
  k_mutex_unlock();
}

