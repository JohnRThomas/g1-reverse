#include "g1_app_symbols.h"
/* named: FUN_00065d8c */
/* globals referenced:
//   0x2000b324  g_nrfx_hal_init_flag         
//   0x5002a000  NRF_GPIOTE1_S                
*/
/* Reconstructed FUN_00065d8c @ 0x65d8c  (parity: 2/300 trials, PROVEN) */
#include <stdint.h>
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
void FUN_00065d8c(int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4){
  if(param_1==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"p_config" /*=0xf6c00*/,"WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_ipc.c" /*=0xf6bc5*/,0x46,param_4);
    assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_ipc.c" /*=0xf6bc5*/,0x46);
  }
 L:
  if(*(volatile uint8_t*)(((uintptr_t)&g_nrfx_hal_init_flag) /*=0x2000b324*/+4)==1){
    int iVar5=0;
    do{
      int iVar1=iVar5*4;
      int iVar3=iVar5+0x144;
      iVar5=iVar5+1;
      *(volatile uint32_t*)(NRF_GPIOTE1_S /*=0x5002a000*/+iVar3*4)=*(volatile uint32_t*)(param_1+iVar1);
    }while(iVar5!=0x10);
    int iVar6=0;
    volatile uint32_t* puVar4=(volatile uint32_t*)(param_1+0x3c);
    do{
      int iVar5b=iVar6+0x164;
      puVar4=puVar4+1;
      iVar6=iVar6+1;
      *(volatile uint32_t*)(NRF_GPIOTE1_S /*=0x5002a000*/+iVar5b*4)=*puVar4;
    }while(iVar6!=0x10);
    *(volatile uint32_t*)(NRF_GPIOTE1_S /*=0x5002a000*/+0x304)=*(volatile uint32_t*)(param_1+0x80);
    return;
  }
  printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"m_cb.state == NRFX_DRV_STATE_INITIALIZED" /*=0xf6c09*/,"WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_ipc.c" /*=0xf6bc5*/,0x47,param_4);
  assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_ipc.c" /*=0xf6bc5*/,0x47);
  goto L;
}

