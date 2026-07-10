#include "g1_app_symbols.h"
/* named: ble_notify_identity_resolved */
/* globals referenced:
//   0x2000ad1c  g_ble_conn_cb_list_head      
*/
/* Reconstructed ble_notify_identity_resolved @ 0x56d1c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t);
void ble_notify_identity_resolved(int param_1){
  int iVar4 = (*(volatile int8_t*)(param_1+3)==0) ? param_1+0x9e : param_1+0x97;
  int iVar2=*(volatile int*)((uintptr_t)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/;
  while(iVar2!=0){
    int t=*(volatile int*)(iVar2+0x10);
    if(t!=0) ((void(*)(int,int,int))t)(param_1,iVar4,param_1+0x90);
    iVar2=*(volatile int*)(iVar2+0x20);
  }
  uint uVar1=((uintptr_t)&tbl_88058) /*=0x88058*/;
  uint uVar3=((uintptr_t)&tbl_87fc8) /*=0x87fec*/;
  while(1){
    if(uVar1<uVar3){
      printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"cb <= _bt_conn_cb_list_end" /*=0xf3a8d*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/,0x85c);
      printk("\tunexpected list end location\n" /*=0xf0d20*/,0,0,0);
      assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/,0x85c);
    }
    if(uVar1<=uVar3) break;
    int t=*(volatile int*)(uVar3+0x10);
    if(t!=0) ((void(*)(int,int,int))t)(param_1,iVar4,param_1+0x90);
    uVar3=uVar3+0x24;
  }
}

