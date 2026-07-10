#include "g1_app_symbols.h"
/* named: net_buf_ref */
/* Reconstructed net_buf_ref @ 0x5f2d4  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a0, unsigned int a1);
extern void printk(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);

void net_buf_ref(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if (param_1 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "buf" /*=0xf45be*/, "WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, 0x202, param_4);
    assert_post_action("WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, 0x202);
  }
  *(volatile unsigned char *)(param_1 + 8) = *(volatile unsigned char *)(param_1 + 8) + 1;
}

