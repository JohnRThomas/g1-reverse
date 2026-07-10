#include "g1_app_symbols.h"
/* named: gatt_dm_attr_alloc */
/* Reconstructed gatt_dm_attr_alloc @ 0x4e8e8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t);
extern int k_calloc(int,int);
int gatt_dm_attr_alloc(int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4){
  int iVar1=((uintptr_t)&cur_service_val) /*=0x2000a154*/;
  uint uVar5=((uint)param_1+3)&0xfffffffcu;
  if(uVar5>0x74){ printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"len <= (128 - sizeof(struct k_mem_block_id) - sizeof(struct data_chunk_item *))" /*=0xf11e7*/,"WEST_TOPDIR/nrf/subsys/bluetooth/gatt_dm.c" /*=0xf11bc*/,0x5b); assert_post_action("WEST_TOPDIR/nrf/subsys/bluetooth/gatt_dm.c" /*=0xf11bc*/,0x5b); }
  uint uVar3=*(volatile uint*)(((uintptr_t)&cur_service_val) /*=0x2000a154*/+0x150);
  uint32_t* puVar2;
  if(uVar3==0 || (uVar3=*(volatile uint*)(((uintptr_t)&cur_service_val) /*=0x2000a154*/+0x158)+uVar5, uVar3>0x74)){
    puVar2=(uint32_t*)(uintptr_t)k_calloc(1,0x78);
    if(puVar2==0) return 0;
    *(volatile uint32_t*)puVar2=0;
    if(*(volatile uint32_t*)(iVar1+0x154)==0){
      *(volatile uint32_t*)(iVar1+0x150)=(uint32_t)(uintptr_t)puVar2;
      *(volatile uint32_t*)(iVar1+0x154)=(uint32_t)(uintptr_t)puVar2;
    } else {
      *(volatile uint32_t*)(uintptr_t)(*(volatile uint32_t*)(iVar1+0x154))=(uint32_t)(uintptr_t)puVar2;
      *(volatile uint32_t*)(iVar1+0x154)=(uint32_t)(uintptr_t)puVar2;
    }
    *(volatile uint32_t*)(iVar1+0x158)=0;
  } else {
    puVar2=(uint32_t*)(uintptr_t)*(volatile uint32_t*)(iVar1+0x154);
  }
  int iVar4=*(volatile int*)(iVar1+0x158);
  *(volatile uint32_t*)(iVar1+0x158)=uVar5+iVar4;
  return (int)(uintptr_t)puVar2+iVar4+4;
}

