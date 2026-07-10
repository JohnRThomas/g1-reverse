#include "g1_app_symbols.h"
/* named: bt_gatt_read */
/* Reconstructed bt_gatt_read @ 0x5c22c  (parity: 300/300 trials, PROVEN) */
extern void assert_post_action(int,...);
extern void printk(int,...);
extern int bt_att_get_mtu(int);
extern int gatt_req_send(int,int,int*,int,int,unsigned);
int bt_gatt_read(int param_1, int *param_2){
  short sVar1; int iVar2; int uVar3; unsigned short uVar4; unsigned uVar5; int uVar6; int uVar7;
  if (param_1==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"conn" /*=0xf3ebd*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,0x13de,0,(int)param_2);
    printk("\tinvalid parameters\n\n" /*=0xf4a0a*/); uVar3=0x13de; assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,uVar3); return uVar3;
  }
  if (param_2==0 || *param_2==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"params && params->func" /*=0xf4c07*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,0x13df,param_1,(int)param_2);
    printk("\tinvalid parameters\n\n" /*=0xf4a0a*/); uVar3=0x13df; assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,uVar3); return uVar3;
  }
  if ((short)param_2[1]==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"params->handle" /*=0xf4cce*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,0x13e0,param_1,(int)param_2);
    printk("\tinvalid parameters\n\n" /*=0xf4a0a*/); uVar3=0x13e0; assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,uVar3); return uVar3;
  }
  if (*(char*)(param_1+0xd)!=7) return 0xffffff80;
  uVar4 = *(unsigned short*)((char*)param_2+0xc);
  if (*(short*)((char*)param_2+6)==0){
    iVar2 = bt_att_get_mtu(param_1);
    uVar5 = (unsigned short)(uVar4+2);
    if (uVar5 <= (unsigned)(iVar2-1U)){
      uVar7=0x12; uVar3=((uintptr_t)&tbl_825bb) /*=0x82603*/; uVar6=((uintptr_t)&tbl_8275f) /*=0x8281b*/; goto LAB;
    }
  }
  sVar1 = bt_att_get_mtu(param_1);
  uVar4 = *(unsigned short*)((char*)param_2+0xc);
  if ((unsigned short)(sVar1-5U) <= *(unsigned short*)((char*)param_2+0xc)) uVar4 = sVar1-5U;
  uVar5 = (unsigned)(unsigned short)(uVar4+4);
  uVar7=0x16; uVar3=((uintptr_t)&rodata_82e05) /*=0x82e05*/; uVar6=((uintptr_t)&tbl_8275f) /*=0x82857*/;
 LAB:
  uVar3 = gatt_req_send(param_1,uVar3,param_2,uVar6,uVar7,uVar5);
  return uVar3;
}

