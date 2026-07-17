#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004c278 @ 0x0004c278
 * public-name: nrf53_ipc_channel_configure
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf53_ipc_channel_configure              <= FUN_0004c278 @ 0x0004c278
 *   nrfx_gppi_task_endpoint_setup            <= FUN_00064f78 @ 0x00064f78
 *   nrfx_gppi_task_endpoint_clear            <= FUN_00064fd4 @ 0x00064fd4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f0a2b                             @ 0x000f0a2b
 *   rodata_f0a5d                             @ 0x000f0a5d
 */
/* Reconstructed FUN_0004c278 @ 0x4c278  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(void*, int);
extern void printk(void*, void*, void*, int, int);
extern unsigned int FUN_000635a4(unsigned int);
extern void nrfx_gppi_task_endpoint_clear(unsigned int, unsigned int);
extern void nrfx_gppi_task_endpoint_setup(unsigned int, unsigned int);

void nrf53_ipc_channel_configure(unsigned int param_1, unsigned int param_2, unsigned int param_3, int param_4)
{
  unsigned int uVar1;
  volatile unsigned int *puVar2;

  if (param_3 > 0xf) {
    printk((void*)((unsigned long)&rodata_99cbd) /*=0x99cbd*/, (void*)((unsigned long)&rodata_f0a5d) /*=0xf0a5d*/, (void*)((unsigned long)&rodata_f0a2b) /*=0xf0a2b*/, 0x1e7, param_4);
    assert_post_action((void*)((unsigned long)&rodata_f0a2b) /*=0xf0a2b*/, 0x1e7);
  }
  uVar1 = FUN_000635a4(param_2);
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
