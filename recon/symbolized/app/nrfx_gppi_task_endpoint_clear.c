#include "g1_app_symbols.h"
/* named: nrfx_gppi_task_endpoint_clear */
/* Reconstructed nrfx_gppi_task_endpoint_clear @ 0x64fd4  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int,unsigned int);
extern void printk(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
void nrfx_gppi_task_endpoint_clear(unsigned int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  if (param_2 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"tep" /*=0xf6a4a*/,"WEST_TOPDIR/modules/hal/nordic/nrfx/helpers/nrfx_gppi_dppi.c" /*=0xf6a09*/,99,param_4);
    assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/helpers/nrfx_gppi_dppi.c" /*=0xf6a09*/,99);
  }
  *(unsigned int *)(param_2 + 0x80) = 0;
  return;
}

