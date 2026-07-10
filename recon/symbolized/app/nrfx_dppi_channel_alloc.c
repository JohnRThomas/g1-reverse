#include "g1_app_symbols.h"
/* named: nrfx_dppi_channel_alloc */
/* Reconstructed nrfx_dppi_channel_alloc @ 0x67e8c  (parity: 1/400 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t nrfx_dppi_channel_alloc(int* param_1, uint8_t* param_2){
  uint8_t r4byte=*(volatile uint8_t*)((char*)param_1+4);
  if(param_2==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"p_channel_id" /*=0xf7a32*/,"WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_wdt.c" /*=0xf79c8*/,0xa2);
    assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_wdt.c" /*=0xf79c8*/,0xa2);
  }
  int iVar6=(int)(((uintptr_t)&m_dppi_channels) /*=0x2000b41c*/ + (uint)r4byte*8);
  while(*(volatile uint8_t*)iVar6 != 1){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"p_cb->state == NRFX_DRV_STATE_INITIALIZED" /*=0xf7052*/,"WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_wdt.c" /*=0xf79c8*/,0xa3);
    assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_wdt.c" /*=0xf79c8*/,0xa3);
  }
  uint8_t bVar1=*(volatile uint8_t*)(iVar6+1);
  uint32_t uVar4=0x0bad0002;
  if(bVar1<8){
    *param_2=bVar1;
    *(volatile uint8_t*)(iVar6+1)=bVar1+1;
    uVar4=0x0bad0000;
    *(volatile uint32_t*)(*(volatile int*)param_1+0x508)=(1u<<bVar1)|*(volatile uint32_t*)(*(volatile int*)param_1+0x508);
  }
  return uVar4;
}

