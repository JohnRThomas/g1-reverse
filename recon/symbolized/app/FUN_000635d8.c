#include "g1_app_symbols.h"
/* named: FUN_000635d8 */
/* Reconstructed FUN_000635d8 @ 0x635d8  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a0, unsigned int a1);
extern void printk(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);

unsigned int FUN_000635d8(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if (param_1 > 1) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "chan >= 0 && chan < (1 + 1)" /*=0xf668a*/, "WEST_TOPDIR/zephyr/drivers/timer/nrf_rtc_timer.c" /*=0xf6659*/, 0xc3, param_4);
    assert_post_action("WEST_TOPDIR/zephyr/drivers/timer/nrf_rtc_timer.c" /*=0xf6659*/, 0xc3);
  }
  return *(volatile unsigned int *)(REG_50015000 /*=0x50015000*/ + (param_1 + 0x150) * 4);
}

