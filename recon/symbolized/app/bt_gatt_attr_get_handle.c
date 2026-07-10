#include "g1_app_symbols.h"
/* named: bt_gatt_attr_get_handle */
/* Reconstructed bt_gatt_attr_get_handle @ 0x5a9f4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned int,...);
extern void assert_post_action(unsigned int,...);
unsigned int bt_gatt_attr_get_handle(unsigned int param_1){
  unsigned int uVar1=param_1; volatile unsigned int* puVar2;
  unsigned int uVar3,uVar4,uVar5,uVar6,uVar7;
  if(param_1!=0 && (uVar1=(unsigned int)*(unsigned short*)(param_1+0x10), uVar1==0)){
    puVar2=(volatile unsigned int*)((uintptr_t)&tbl_88058) /*=0x88058*/; uVar4=1;
    while(1){
      if((volatile unsigned int*)((uintptr_t)&tbl_88058) /*=0x88070*/ < puVar2){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"static_svc <= _bt_gatt_service_static_list_end" /*=0xf49a5*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,0x713);
        printk("\tunexpected list end location\n" /*=0xf0d20*/);
        assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,0x713);
      }
      if((volatile unsigned int*)((uintptr_t)&tbl_88058) /*=0x88070*/ <= puVar2) break;
      uVar7=puVar2[0]; uVar6=puVar2[1];
      if((param_1<uVar7)||(((uVar6*0x14+uVar7)-0x14)<param_1)){
        uVar3=(uVar4+uVar6)&((uintptr_t)&tbl_ffc8) /*=0xffff*/;
      } else {
        for(uVar5=0; uVar3=(uVar4+uVar5)&((uintptr_t)&tbl_ffc8) /*=0xffff*/, uVar5!=uVar6; uVar5=uVar5+1){
          if(param_1==uVar5*0x14+uVar7) return uVar3;
        }
      }
      puVar2=puVar2+2; uVar4=uVar3;
    }
  }
  return uVar1;
}

