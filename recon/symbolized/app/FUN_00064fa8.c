#include "g1_app_symbols.h"
/* named: FUN_00064fa8 */
/* Reconstructed FUN_00064fa8 @ 0x64fa8  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int,unsigned int);
extern void printk(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
void FUN_00064fa8(unsigned int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  if (param_2 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"eep" /*=0xf6a46*/,"WEST_TOPDIR/modules/hal/nordic/nrfx/helpers/nrfx_gppi_dppi.c" /*=0xf6a09*/,0x5c,param_4);
    assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/helpers/nrfx_gppi_dppi.c" /*=0xf6a09*/,0x5c);
  }
  *(unsigned int *)(param_2 + 0x80) = 0;
  return;
}

