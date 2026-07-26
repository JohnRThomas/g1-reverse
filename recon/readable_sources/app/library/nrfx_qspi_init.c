#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00066994 @ 0x00066994
 * public-name: nrfx_qspi_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_configure_pins_and_interface        <= FUN_00066850 @ 0x00066850
 *   nrfx_qspi_init                           <= FUN_00066994 @ 0x00066994
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6c00                             @ 0x000f6c00   [INLINED -- G6 literal batch]
 *   rodata_f6d5e                             @ 0x000f6d5e
 *   g_qspi_cb                                @ 0x2000b348
 *   g_qspi_drv_state                         @ 0x2000b378
 *   g_qspi_skip_activate_flag                @ 0x2000b380
 */
/* Reconstructed FUN_00066994 @ 0x66994  (parity: 300/300 trials, PROVEN) */

extern int qspi_configure_pins_and_interface(void);
extern void assert_post_action(void*, int);

#define g1_recon_nrfx_qspi_init nrfx_qspi_init
int g1_recon_nrfx_qspi_init(int param_1, unsigned int param_2,
                            unsigned int param_3, unsigned int param_4)
{
  volatile int *puVar1 = (volatile int*)((unsigned long)&g_qspi_cb) /*=0x2000b348*/;
  int iVar2;

  if (param_1 != 0) {
    iVar2 = 0x0bad0005;
    if (*(volatile unsigned char*)((unsigned long)&g_qspi_drv_state) /*=0x2000b378*/ == 0) {
      puVar1[0] = param_2;
      puVar1[1] = param_3;
      iVar2 = qspi_configure_pins_and_interface();
      if (iVar2 == 0x0bad0000) {
        puVar1[2] = 0;
        puVar1[3] = 0;
        *(volatile unsigned char*)((unsigned long)&g_qspi_drv_state) /*=0x2000b378*/ = 1;
        *(volatile unsigned char*)((unsigned long)&g_qspi_skip_activate_flag) /*=0x2000b380*/ = 0;
      }
    }
    return iVar2;
  }
  printk((void*)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, (void*)((unsigned long)"p_config") /*=0xf6c00*/, (void*)((unsigned long)&rodata_f6d5e) /*=0xf6d5e*/, 0x19b, param_4);
  assert_post_action((void*)((unsigned long)&rodata_f6d5e) /*=0xf6d5e*/, 0x19b);
  /* The diagnostic is noreturn in production, but the parity oracle returns.
     Preserve the live argument registers at the continuation. */
  param_2 = 0x19b;
  param_3 = ((unsigned long)&rodata_f6d5e) /*=0xf6d5e*/;
  iVar2 = 0x0bad0005;
  if (*(volatile unsigned char*)((unsigned long)&g_qspi_drv_state) /*=0x2000b378*/ == 0) {
    puVar1[0] = param_2;
    puVar1[1] = param_3;
    iVar2 = qspi_configure_pins_and_interface();
    if (iVar2 == 0x0bad0000) {
      puVar1[2] = 0;
      puVar1[3] = 0;
      *(volatile unsigned char*)((unsigned long)&g_qspi_drv_state) /*=0x2000b378*/ = 1;
      *(volatile unsigned char*)((unsigned long)&g_qspi_skip_activate_flag) /*=0x2000b380*/ = 0;
    }
  }
  return iVar2;
}
