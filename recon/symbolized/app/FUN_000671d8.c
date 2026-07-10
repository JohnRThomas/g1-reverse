#include "g1_app_symbols.h"
/* named: FUN_000671d8 */
/* Reconstructed FUN_000671d8 @ 0x671d8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00066d78(void);
extern int FUN_00066ec0(int);
extern int assert_post_action(int,int);
extern int printk(int,...);
int FUN_000671d8(int param_1, int param_2, uint32_t param_3, uint32_t param_4){
  int r0src = param_1;
  if(param_2 == 0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "p_config" /*=0xf6c00*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c" /*=0xf6df0*/, 0x1ff, param_4);
    assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c" /*=0xf6df0*/, 0x1ff);
    r0src = "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c" /*=0xf6df0*/;
  }
  uint32_t off = (uint32_t)*(volatile uint8_t*)(r0src+4) * 0x24;
  uint32_t ip = ((uintptr_t)&g_nrfx_spim_cb) /*=0x2000b384*/;
  int iVar3 = ip + off;
  uint8_t r7 = *(volatile uint8_t*)(iVar3+0x1c);
  if(r7 != 0){
    return 0x0bad0005;
  }
  *(volatile uint32_t*)(ip + off) = param_3;
  *(volatile uint32_t*)(iVar3+4) = param_4;
  int iVar1 = FUN_00066d78();
  if(iVar1 == 0x0bad0000){
    FUN_00066ec0(param_1);
    *(volatile uint8_t*)(iVar3+0x1d) = r7;
    *(volatile uint8_t*)(iVar3+0x1c) = 1;
  }
  return iVar1;
}

