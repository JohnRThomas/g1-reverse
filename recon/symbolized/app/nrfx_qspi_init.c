#include "g1_app_symbols.h"
/* named: nrfx_qspi_init */
/* globals referenced:
//   0x2000b348  g_qspi_cb                    
*/
/* Reconstructed nrfx_qspi_init @ 0x66994  (parity: 300/300 trials, PROVEN) */

extern int qspi_configure_pins_and_interface(void);
extern void assert_post_action(void*, int);
extern void printk(void*, void*, void*, int, unsigned int);

int nrfx_qspi_init(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  volatile int *puVar1 = (volatile int*)((uintptr_t)&g_qspi_cb) /*=0x2000b348*/;
  int iVar2;

  if (param_1 != 0) {
    iVar2 = 0x0bad0005;
    if (*(volatile unsigned char*)((uintptr_t)&g_qspi_drv_state) /*=0x2000b378*/ == 0) {
      puVar1[0] = param_2;
      puVar1[1] = param_3;
      iVar2 = qspi_configure_pins_and_interface();
      if (iVar2 == 0x0bad0000) {
        puVar1[2] = 0;
        puVar1[3] = 0;
        *(volatile unsigned char*)((uintptr_t)&g_qspi_drv_state) /*=0x2000b378*/ = 1;
        *(volatile unsigned char*)((uintptr_t)&g_qspi_skip_activate_flag) /*=0x2000b380*/ = 0;
      }
    }
    return iVar2;
  }
  printk((void*)"ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, (void*)"p_config" /*=0xf6c00*/, (void*)"WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c" /*=0xf6d5e*/, 0x19b, param_4);
  assert_post_action((void*)"WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c" /*=0xf6d5e*/, 0x19b);
  return 0;
}

