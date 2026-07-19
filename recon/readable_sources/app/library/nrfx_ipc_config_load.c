#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065d8c @ 0x00065d8c
 * public-name: nrfx_ipc_config_load
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_ipc_config_load                     <= FUN_00065d8c @ 0x00065d8c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6bc5                             @ 0x000f6bc5
 *   rodata_f6c00                             @ 0x000f6c00
 *   rodata_f6c09                             @ 0x000f6c09
 *   g_nrfx_hal_init_flag                     @ 0x2000b324
 */
/* Reconstructed FUN_00065d8c @ 0x65d8c  (parity: 2/300 trials, PROVEN) */
#include <stdint.h>
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
void nrfx_ipc_config_load(int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4){
  if(param_1==0){
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f6c00) /*=0xf6c00*/,((unsigned long)&rodata_f6bc5) /*=0xf6bc5*/,0x46,param_4);
    assert_post_action(((unsigned long)&rodata_f6bc5) /*=0xf6bc5*/,0x46);
  }
 L:
  if(*(volatile uint8_t*)(((unsigned long)&g_nrfx_hal_init_flag) /*=0x2000b324*/+4)==1){
    int iVar5=0;
    do{
      int iVar1=iVar5*4;
      int iVar3=iVar5+0x144;
      iVar5=iVar5+1;
      *(volatile uint32_t*)(0x5002a000UL+iVar3*4)=*(volatile uint32_t*)(param_1+iVar1);
    }while(iVar5!=0x10);
    int iVar6=0;
    volatile uint32_t* puVar4=(volatile uint32_t*)(param_1+0x3c);
    do{
      int iVar5b=iVar6+0x164;
      puVar4=puVar4+1;
      iVar6=iVar6+1;
      *(volatile uint32_t*)(0x5002a000UL+iVar5b*4)=*puVar4;
    }while(iVar6!=0x10);
    *(volatile uint32_t*)(0x5002a000UL+0x304)=*(volatile uint32_t*)(param_1+0x80);
    return;
  }
  printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f6c09) /*=0xf6c09*/,((unsigned long)&rodata_f6bc5) /*=0xf6bc5*/,0x47,param_4);
  assert_post_action(((unsigned long)&rodata_f6bc5) /*=0xf6bc5*/,0x47);
  goto L;
}
