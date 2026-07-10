#include "g1_app_symbols.h"
/* named: FUN_00064f48 */
/* Reconstructed FUN_00064f48 @ 0x64f48  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern unsigned int assert_post_action(int a, int b);
void FUN_00064f48(unsigned int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int val = param_1;
  if (param_2 == 0) {
    printk("eep" /*=0xf6a46*/, "ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/helpers/nrfx_gppi_dppi.c" /*=0xf6a09*/, 0x44, param_4);
    val = assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/helpers/nrfx_gppi_dppi.c" /*=0xf6a09*/, 0x44);
  }
  *(volatile unsigned int *)(param_2 + 0x80) = val | 0x80000000UL;
}

