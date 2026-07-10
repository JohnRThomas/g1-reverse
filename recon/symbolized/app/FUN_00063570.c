#include "g1_app_symbols.h"
/* named: FUN_00063570 */
/* Reconstructed FUN_00063570 @ 0x63570  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern unsigned int assert_post_action(int a, int b);
unsigned int FUN_00063570(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int idx = param_1;
  if (1 < param_1) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "chan >= 0 && chan < (1 + 1)" /*=0xf668a*/, "WEST_TOPDIR/zephyr/drivers/timer/nrf_rtc_timer.c" /*=0xf6659*/, 0x86, param_4);
    idx = assert_post_action("WEST_TOPDIR/zephyr/drivers/timer/nrf_rtc_timer.c" /*=0xf6659*/, 0x86);
  }
  return REG_50015140 /*=0x50015140*/ + idx * 4;
}

