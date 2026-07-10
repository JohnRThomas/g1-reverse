#include "g1_app_symbols.h"
/* named: nrfx_nvmc_page_erase */
/* globals referenced:
//   0x50039000  NRF_NVMC_S                   
*/
/* Reconstructed nrfx_nvmc_page_erase @ 0x65f1c  (parity: 300/300 trials, PROVEN) */

extern void nvmc_readonly_mode_set(void);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void assert_post_action(unsigned int a, unsigned int b);

unsigned int nrfx_nvmc_page_erase(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if ((unsigned int)param_1 >= FLASH_OFF_100000 /*=0x100000*/) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "is_valid_address(addr, 0)" /*=0xf6c8e*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_nvmc.c" /*=0xf6c32*/, 0x107, param_4);
    assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_nvmc.c" /*=0xf6c32*/, 0x107);
    return 0x0bad000a;
  }
  if (((unsigned int)param_1 & 0xfff) != 0) {
    return 0x0bad000a;
  }
  *(volatile unsigned int *)(NRF_NVMC_S /*=0x50039000*/ + 0x584) = 2;
  *(volatile unsigned int *)(NRF_NVMC_S /*=0x50039000*/ + 0x504) = 2;
  *param_1 = 0xffffffff;
  while (((int)(*(volatile unsigned int *)(NRF_NVMC_S /*=0x50039000*/ + 0x400) << 0x1f)) >= 0) {}
  nvmc_readonly_mode_set();
  return 0x0bad0000;
}

