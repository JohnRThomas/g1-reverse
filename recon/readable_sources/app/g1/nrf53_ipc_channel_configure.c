#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0004c278 @ 0x0004c278
 * public-name: nrf53_ipc_channel_configure
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf53_ipc_channel_configure              <= FUN_0004c278 @ 0x0004c278
 *   rtc_timer_cc_reg_get                     <= FUN_000635a4 @ 0x000635a4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0a2b                             @ 0x000f0a2b   [INLINED -- G6 literal batch]
 *   rodata_f0a5d                             @ 0x000f0a5d   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0004c278 @ 0x4c278  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(void*, int);
extern unsigned int rtc_timer_cc_reg_get(unsigned int);
extern void nrfx_gppi_task_endpoint_clear(unsigned int, unsigned int);
extern void nrfx_gppi_task_endpoint_setup(unsigned int, unsigned int);

void nrf53_ipc_channel_configure(unsigned int param_1, unsigned int param_2, unsigned int param_3, int param_4)
{
  unsigned int uVar1;
  volatile unsigned int *puVar2;

  if (param_3 > 0xf) {
    printk((void*)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, (void*)((unsigned long)"index < 16") /*=0xf0a5d*/, (void*)((unsigned long)"WEST_TOPDIR/modules/hal/nordic/nrfx/hal/nrf_ipc.h") /*=0xf0a2b*/, 0x1e7, param_4);
    assert_post_action((void*)((unsigned long)"WEST_TOPDIR/modules/hal/nordic/nrfx/hal/nrf_ipc.h") /*=0xf0a2b*/, 0x1e7);
  }
  uVar1 = rtc_timer_cc_reg_get(param_2);
  puVar2 = (volatile unsigned int*)(0x5002a180UL + param_3*4);
  if (param_4 == 0) {
    nrfx_gppi_task_endpoint_clear(param_1, uVar1);
    *puVar2 = 0;
  } else {
    nrfx_gppi_task_endpoint_setup(param_1, uVar1);
    *puVar2 = param_1 | 0x80000000;
  }
  return;
}
