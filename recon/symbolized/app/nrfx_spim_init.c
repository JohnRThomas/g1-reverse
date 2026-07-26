#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000671d8 @ 0x000671d8
 * public-name: nrfx_spim_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_pin_freq_config_validate            <= FUN_00066d78 @ 0x00066d78
 *   nrfx_spim_configure                      <= FUN_00066ec0 @ 0x00066ec0
 *   nrfx_spim_init                           <= FUN_000671d8 @ 0x000671d8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6c00                             @ 0x000f6c00   [INLINED -- G6 literal batch]
 *   rodata_f6df0                             @ 0x000f6df0
 *   g_nrfx_spim_cb                           @ 0x2000b384
 */
/* Reconstructed FUN_000671d8 @ 0x671d8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern int nrfx_pin_freq_config_validate(void);
extern int nrfx_spim_configure(int);
extern int assert_post_action(int,int);
int nrfx_spim_init(int param_1, int param_2, uint32_t param_3, uint32_t param_4){
  int r0src = param_1;
  if(param_2 == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"p_config") /*=0xf6c00*/, ((unsigned long)&rodata_f6df0) /*=0xf6df0*/, 0x1ff, param_4);
    assert_post_action(((unsigned long)&rodata_f6df0) /*=0xf6df0*/, 0x1ff);
    r0src = ((unsigned long)&rodata_f6df0) /*=0xf6df0*/;
  }
  uint32_t off = (uint32_t)*(volatile uint8_t*)(r0src+4) * 0x24;
  uint32_t ip = ((unsigned long)&g_nrfx_spim_cb) /*=0x2000b384*/;
  int iVar3 = ip + off;
  uint8_t r7 = *(volatile uint8_t*)(iVar3+0x1c);
  if(r7 != 0){
    return 0x0bad0005;
  }
  *(volatile uint32_t*)(ip + off) = param_3;
  *(volatile uint32_t*)(iVar3+4) = param_4;
  int iVar1 = nrfx_pin_freq_config_validate();
  if(iVar1 == 0x0bad0000){
    nrfx_spim_configure(param_1);
    *(volatile uint8_t*)(iVar3+0x1d) = r7;
    *(volatile uint8_t*)(iVar3+0x1c) = 1;
  }
  return iVar1;
}
