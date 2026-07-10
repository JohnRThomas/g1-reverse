#include "g1_app_symbols.h"
/* named: FUN_000635a4 */
/* Reconstructed FUN_000635a4 @ 0x635a4  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a0, unsigned int a1);
extern void printk(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);

unsigned int FUN_000635a4(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1;
  if (param_1 > 1) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "chan >= 0 && chan < (1 + 1)" /*=0xf668a*/, "WEST_TOPDIR/zephyr/drivers/timer/nrf_rtc_timer.c" /*=0xf6659*/, 0x8d, param_4);
    assert_post_action("WEST_TOPDIR/zephyr/drivers/timer/nrf_rtc_timer.c" /*=0xf6659*/, 0x8d);
  }
  uVar1 = REG_50015044 /*=0x50015044*/;
  if (param_1 == 0) {
    uVar1 = 0;
  }
  return uVar1;
}

