#include "g1_app_symbols.h"
/* named: gatt_indicate */
/* Reconstructed gatt_indicate @ 0x5b270  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int bt_att_create_pdu(unsigned,int,int);
extern int bt_att_req_alloc(int,int);
extern void bt_att_req_free(int);
extern int bt_att_req_send(unsigned,int);
extern int FUN_0005b0dc(unsigned,unsigned,int);
extern unsigned net_buf_simple_add(int,int);
extern void bt_att_set_tx_meta_data(int,int,int,int);
extern void FUN_00082a42(unsigned,int,void*);
extern int bt_gatt_check_perm(unsigned,unsigned,int);
extern void memcpy(void*,unsigned,unsigned);
int gatt_indicate(unsigned param_1, unsigned short param_2, int param_3)
{
  unsigned short uVar1; unsigned uVar2; int iVar3, iVar5; unsigned short *puVar4;
  unsigned local_28, local_24;
  iVar3 = bt_gatt_check_perm(param_1, *(unsigned*)(param_3+4), 0x94);
  if (iVar3 == 0) {
    iVar3 = FUN_0005b0dc(param_1, *(unsigned*)(param_3+4), 2);
    if (iVar3 == 0) {
      local_24 = "Device is not subscribed to characteristic" /*=0xf4aeb*/; local_28 = 2; iVar3 = -0x16;
      FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1080, &local_28);
    } else {
      uVar1 = *(unsigned short*)(param_3+0x14);
      iVar3 = bt_att_req_alloc("eflash command end .......\n" /*=0xf0000*/, 0);
      uVar2 = ((uintptr_t)&tbl_825bb) /*=0x825d5*/;
      iVar5 = uVar1 + 2;
      if (iVar3 != 0) {
        *(volatile int*)(iVar3+0x14) = iVar5;
        *(volatile unsigned char*)(iVar3+0x11) = 0x1d;
        *(volatile unsigned*)(iVar3+0xc) = 0;
        *(volatile unsigned*)(iVar3+4) = uVar2;
        *(volatile int*)(iVar3+0x18) = param_3;
        iVar5 = bt_att_create_pdu(param_1, 0x1d, iVar5);
        if (iVar5 != 0) {
          bt_att_set_tx_meta_data(iVar5, 0, 0, 1);
          puVar4 = (unsigned short*)net_buf_simple_add(iVar5+0xc, 2);
          *(volatile unsigned short*)puVar4 = param_2;
          net_buf_simple_add(iVar5+0xc, *(unsigned short*)(param_3+0x14));
          memcpy(puVar4+1, *(unsigned*)(param_3+0x10), *(unsigned short*)(param_3+0x14));
          *(volatile int*)(iVar3+8) = iVar5;
          iVar5 = bt_att_req_send(param_1, iVar3);
          if (iVar5 == 0) return 0;
          bt_att_req_free(iVar3);
          return iVar5;
        }
        local_24 = "No buffer available to send indication" /*=0xf4b16*/; local_28 = 2;
        FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1080, &local_28);
        bt_att_req_free(iVar3);
      }
      iVar3 = -0xc;
    }
  } else {
    iVar3 = -1;
    local_24 = "Link is not encrypted" /*=0xf4ad5*/; local_28 = 2;
    FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1080, &local_28);
  }
  return iVar3;
}

