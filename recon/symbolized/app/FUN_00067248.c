#include "g1_app_symbols.h"
/* named: FUN_00067248 */
/* Reconstructed FUN_00067248 @ 0x67248  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef unsigned int uint;
extern void arch_irq_disable(int);
extern void spim_pin_uninit(uint32_t);
extern void assert_post_action(uint32_t,int);
extern void printk(uint32_t,uint32_t,...);
extern void spim_abort(int, int);

void FUN_00067248(int *param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
  uint uVar3 = *(uint8_t*)((char*)param_1 + 4);
  if (*(volatile char*)(((uintptr_t)&g_nrfx_spim_cb) /*=0x2000b384*/ + uVar3*0x24 + 0x1c) == 0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "p_cb->state != NRFX_DRV_STATE_UNINITIALIZED" /*=0xf6e3a*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c" /*=0xf6df0*/, 0x255, param_4);
    assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c" /*=0xf6df0*/, 0x255);
  }
  arch_irq_disable((*param_1 << 0xc) >> 0x18);
  if (*(volatile int*)(((uintptr_t)&g_nrfx_spim_cb) /*=0x2000b384*/ + uVar3*0x24) != 0){
    *(volatile uint32_t*)(*param_1 + 0x308) = ((uintptr_t)&rodata_80152) /*=0x80152*/;
    spim_abort(*param_1, ((uintptr_t)&g_nrfx_spim_cb) /*=0x2000b384*/ + uVar3*0x24);
  }
  int iVar4 = uVar3*0x24 + ((uintptr_t)&g_nrfx_spim_cb) /*=0x2000b384*/;
  int iVar2 = *param_1;
  uint32_t uVar5 = *(uint32_t*)(iVar2 + 0x50c);
  uint32_t uVar6 = *(uint32_t*)(iVar2 + 0x510);
  if ((int)((uint32_t)*(uint8_t*)(iVar4 + 0x1e) << 0x1f) >= 0){
    spim_pin_uninit(*(uint32_t*)(iVar2 + 0x508));
    spim_pin_uninit(uVar6);
    spim_pin_uninit(uVar5);
    spim_pin_uninit(*(uint32_t*)(iVar4 + 0x20));
    if ((char)*(uint8_t*)((char*)param_1+4) != 0){
      uVar5 = *(uint32_t*)(*param_1 + 0x514);
      spim_pin_uninit(*(uint32_t*)(*param_1 + 0x56c));
      spim_pin_uninit(uVar5);
    }
  }
  *(volatile uint8_t*)(uVar3*0x24 + ((uintptr_t)&g_nrfx_spim_cb) /*=0x2000b384*/ + 0x1c) = 0;
}

