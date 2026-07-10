#include "g1_app_symbols.h"
/* named: nrf53_ipc_channel_configure */
/* Reconstructed nrf53_ipc_channel_configure @ 0x4c278  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(void*, int);
extern void printk(void*, void*, void*, int, int);
extern unsigned int FUN_000635a4(unsigned int);
extern void nrfx_gppi_task_endpoint_clear(unsigned int, unsigned int);
extern void nrfx_gppi_task_endpoint_setup(void);

void nrf53_ipc_channel_configure(unsigned int param_1, unsigned int param_2, unsigned int param_3, int param_4)
{
  unsigned int uVar1;
  volatile unsigned int *puVar2;

  if (param_3 > 0xf) {
    printk((void*)"ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, (void*)"index < 16" /*=0xf0a5d*/, (void*)"WEST_TOPDIR/modules/hal/nordic/nrfx/hal/nrf_ipc.h" /*=0xf0a2b*/, 0x1e7, param_4);
    assert_post_action((void*)"WEST_TOPDIR/modules/hal/nordic/nrfx/hal/nrf_ipc.h" /*=0xf0a2b*/, 0x1e7);
  }
  uVar1 = FUN_000635a4(param_2);
  puVar2 = (volatile unsigned int*)(REG_5002a180 /*=0x5002a180*/ + param_3*4);
  if (param_4 == 0) {
    nrfx_gppi_task_endpoint_clear(param_1, uVar1);
    *puVar2 = 0;
  } else {
    nrfx_gppi_task_endpoint_setup();
    *puVar2 = param_1 | 0x80000000;
  }
  return;
}

