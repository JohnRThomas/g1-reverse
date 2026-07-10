#include "g1_app_symbols.h"
/* named: ble_conn_process_complete_or_disconnect */
/* globals referenced:
//   0x00088108  log_module_bt_conn           
//   0x2000ad1c  g_ble_conn_cb_list_head      
*/
/* Reconstructed ble_conn_process_complete_or_disconnect @ 0x570a0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void ancs_disconnected(void);
extern void ble_conn_unref(int);
extern int send_conn_le_param_update(int,void*);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
extern int atomic_and_2(volatile unsigned*,unsigned);
extern void FUN_000813ca(unsigned,unsigned,void*);
extern void bt_l2cap_disconnected(int);

void ble_conn_process_complete_or_disconnect(int param_1){
  int iVar5 = param_1 - 0x60;
  unsigned uVar1, uVar3;
  int iVar2;
  if(*(volatile char*)(param_1-0x53) == 0){
    bt_l2cap_disconnected(iVar5);
    for(iVar2 = *(volatile int*)((uintptr_t)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/;
        uVar1 = ((uintptr_t)&tbl_88058) /*=0x88058*/, uVar3 = ((uintptr_t)&tbl_87fc8) /*=0x87fec*/, iVar2 != 0;
        iVar2 = *(volatile int*)(iVar2+0x20)){
      if(*(void**)(iVar2+4) != 0)
        (*(void(**)(int,unsigned char))(iVar2+4))(iVar5,*(volatile uint8_t*)(param_1-0x54));
    }
    while(1){
      if(uVar1 < uVar3){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"cb <= _bt_conn_cb_list_end" /*=0xf3a8d*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/,0x5fe);
        printk("\tunexpected list end location\n" /*=0xf0d20*/);
        assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/,0x5fe);
      }
      if(uVar1 <= uVar3) break;
      if(*(void**)(uVar3+4) != 0)
        (*(void(**)(int,unsigned char))(uVar3+4))(iVar5,*(volatile uint8_t*)(param_1-0x54));
      uVar3 = uVar3 + 0x24;
    }
    ble_conn_unref(iVar5);
    return;
  }
  if(*(volatile char*)(param_1-0x5e) != 1) return;
  volatile unsigned *puVar4 = (volatile unsigned*)(param_1-0x5c);
  unsigned local_20, local_1c, local_2c, local_30;
  int iStack_28;
  iVar2 = atomic_and_2(puVar4, 0xfffffdffU);
  if((int)(iVar2 << 0x16) < 0){
    local_20 = *(volatile unsigned*)(param_1+0x48);
    local_1c = *(volatile unsigned*)(param_1+0x50);
    iStack_28 = send_conn_le_param_update(iVar5,&local_20);
    local_2c = "Send LE param update failed (err %d)" /*=0xf3dff*/;
    if(iStack_28 == 0){
      atomic_and_2(puVar4, 0xfffffeffU);
      goto LAB;
    }
  } else {
    local_20 = 0x00280018U;
    local_1c = 0x2a0000U;
    iStack_28 = send_conn_le_param_update(iVar5,&local_20);
    local_2c = "Send auto LE param update failed (err %d)" /*=0xf3e24*/;
    if(iStack_28 == 0){
      *puVar4 = *puVar4 | 0x100;
      goto LAB;
    }
  }
  local_30 = 3;
  FUN_000813ca(((uintptr_t)&log_module_bt_conn) /*=0x88108*/, 0x1880, &local_30);
LAB:
  *puVar4 = *puVar4 | 0x80;
  (void)local_2c; (void)local_1c;
  return;
}

