#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00065f1c @ 0x00065f1c
 * public-name: nrfx_nvmc_page_erase
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nvmc_readonly_mode_set                   <= FUN_00065ef0 @ 0x00065ef0
 *   nrfx_nvmc_page_erase                     <= FUN_00065f1c @ 0x00065f1c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6c32                             @ 0x000f6c32
 *   rodata_f6c8e                             @ 0x000f6c8e   [INLINED -- G6 literal batch]
 *   NRF_NVMC_S                               @ 0x50039000
 */
/* Reconstructed FUN_00065f1c @ 0x65f1c  (parity: 300/300 trials, PROVEN) */

extern void nvmc_readonly_mode_set(void);
extern void assert_post_action(unsigned int a, unsigned int b);

unsigned int nrfx_nvmc_page_erase(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if ((unsigned int)param_1 >= 0x100000u) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"is_valid_address(addr, 0)") /*=0xf6c8e*/, ((unsigned long)&rodata_f6c32) /*=0xf6c32*/, 0x107, param_4);
    assert_post_action(((unsigned long)&rodata_f6c32) /*=0xf6c32*/, 0x107);
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
