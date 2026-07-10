#include "g1_app_symbols.h"
/* named: nrfx_gppi_task_endpoint_setup */
/* Reconstructed nrfx_gppi_task_endpoint_setup @ 0x64f78  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern unsigned int assert_post_action(int a, int b);
void nrfx_gppi_task_endpoint_setup(unsigned int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int val = param_1;
  if (param_2 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "tep" /*=0xf6a4a*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/helpers/nrfx_gppi_dppi.c" /*=0xf6a09*/, 0x4a, param_4);
    val = assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/helpers/nrfx_gppi_dppi.c" /*=0xf6a09*/, 0x4a);
  }
  *(volatile unsigned int *)(param_2 + 0x80) = val | 0x80000000UL;
}

