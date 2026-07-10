#include "g1_app_symbols.h"
/* named: FUN_00054528 */
/* Reconstructed FUN_00054528 @ 0x54528  (parity: 300/300 trials, PROVEN) */
extern int bt_hci_cmd_create(int,int);
extern void bt_hci_cmd_send_or_create(int,int);
extern void ble_conn_unref(int);
extern int ble_conn_lookup_masked(unsigned,int);
extern int ble_notify_disconnected(int,void*);
extern unsigned short* net_buf_simple_add(int,int);
extern void FUN_00080ea2(int,int,void*);
extern void le_conn_param_neg_reply(unsigned,int);
void FUN_00054528(int param_1){
  unsigned short *src = *(unsigned short**)(param_1+0xc);
  unsigned uVar1 = *(volatile unsigned short*)src;
  unsigned uVar5 = uVar1 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
  unsigned short local_20 = *(volatile unsigned short*)((char*)src+2);
  unsigned short local_1e = *(volatile unsigned short*)((char*)src+4);
  unsigned short local_1c = *(volatile unsigned short*)((char*)src+6);
  unsigned short local_1a = *(volatile unsigned short*)((char*)src+8);
  int iVar2 = ble_conn_lookup_masked(uVar5,1);
  if (iVar2 == 0){
    unsigned local_30=3, local_2c="Unable to lookup conn for handle %u" /*=0xf2db7*/, uStack_28=uVar5;
    (void)local_2c;(void)uStack_28;
    FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x1840, &local_30);
    le_conn_param_neg_reply(uVar5, 2);
  } else {
    int iVar3 = ble_notify_disconnected(iVar2, &local_20);
    if (iVar3 == 0){
      le_conn_param_neg_reply(uVar5, 0x1e);
    } else {
      iVar3 = bt_hci_cmd_create(0x2020, 0xe);
      if (iVar3 != 0){
        volatile unsigned short *p = (volatile unsigned short*)net_buf_simple_add(iVar3+0xc, 0xe);
        *p = (unsigned short)uVar1;
        *(volatile unsigned*)((char*)p+0xa) = 0;
        p[1] = local_20;
        p[2] = local_1e;
        p[3] = local_1c;
        p[4] = local_1a;
        bt_hci_cmd_send_or_create(0x2020, iVar3);
      }
    }
    ble_conn_unref(iVar2);
  }
}

