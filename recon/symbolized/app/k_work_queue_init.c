#include "g1_app_symbols.h"
/* named: k_work_queue_init */
/* Reconstructed k_work_queue_init @ 0x730b4  (parity: 300/300 trials, PROVEN) */

extern int printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern int assert_post_action(unsigned int a, unsigned int b);
extern void memset_bytes(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void k_work_queue_init(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r0 = (unsigned int)param_1;
  if (param_1 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "queue != ((void *)0)" /*=0xf824d*/, "WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/, 0x2b9);
    r0 = assert_post_action("WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/, 0x2b9);
  }
  memset_bytes(r0, 0, 0xf8, param_4, param_4);
}

