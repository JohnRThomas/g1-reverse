#include "g1_app_symbols.h"
/* named: FUN_000538f8 */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
*/
/* Reconstructed FUN_000538f8 @ 0x538f8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int net_buf_pool_get(unsigned);
extern int net_buf_id(int);
extern void net_buf_unref(void);
extern void FUN_00072880(unsigned);
extern void atomic_or(int);
extern void FUN_00080ea2(unsigned,unsigned,void*);
extern void atomic_and_3(int,int);

void FUN_000538f8(unsigned param_1, int param_2, int param_3, unsigned param_4){
  int iVar3 = net_buf_pool_get(*(unsigned char*)(param_3 + 10));
  if(*(volatile int*)((uintptr_t)&g_hci_cmd_pool) /*=0x20003b4c*/ == iVar3){
    int iVar4 = net_buf_id(param_3);
    if(*(volatile unsigned short*)(iVar4*0xc + ((uintptr_t)&bt_hci_cmd_data) /*=0x2000abf4*/ + 2) == (unsigned short)param_1){
      if(*(volatile int*)(((uintptr_t)&g_ble_dev_state) /*=0x20002000*/ + 0x140) != 0){
        net_buf_unref();
        *(volatile int*)(((uintptr_t)&g_ble_dev_state) /*=0x20002000*/ + 0x140) = 0;
      }
      {
        int i = net_buf_id(param_3);
        if(*(volatile int*)(i*0xc + ((uintptr_t)&bt_hci_cmd_data) /*=0x2000abf4*/ + 4) != 0 && param_2 == 0){
          int j = net_buf_id(param_3);
          int *piVar5 = *(int* volatile*)(j*0xc + ((uintptr_t)&bt_hci_cmd_data) /*=0x2000abf4*/ + 4);
          unsigned uVar6 = (unsigned)piVar5[1] >> 5;
          if((char)piVar5[2] == 0)
            atomic_and_3(piVar5[0] + uVar6*4, ~(1 << (piVar5[1] & 0x1f)));
          else
            atomic_or(piVar5[0] + uVar6*4);
        }
      }
      {
        int k = net_buf_id(param_3);
        if(*(volatile int*)(k*0xc + ((uintptr_t)&bt_hci_cmd_data) /*=0x2000abf4*/ + 8) != 0){
          int m = net_buf_id(param_3);
          *(volatile char*)(((uintptr_t)&bt_hci_cmd_data) /*=0x2000abf4*/ + m*0xc) = (char)param_2;
          int n = net_buf_id(param_3);
          FUN_00072880(*(volatile unsigned*)(n*0xc + ((uintptr_t)&bt_hci_cmd_data) /*=0x2000abf4*/ + 8));
        }
      }
    } else {
      int i = net_buf_id(param_3);
      unsigned st[8];
      st[0]=4; st[3]="OpCode 0x%04x completed instead of expected 0x%04x" /*=0xf2f8e*/; st[4]=param_1; st[7]=*(volatile unsigned short*)(i*0xc + ((uintptr_t)&bt_hci_cmd_data) /*=0x2000abf4*/ + 2);
      FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x2080, st);
    }
  } else {
    unsigned char bVar1 = *(unsigned char*)(param_3 + 10);
    unsigned st[8];
    st[2] = net_buf_pool_get((unsigned)bVar1);
    st[0]=6; st[1]="opcode 0x%04x pool id %u pool %p != &hci_cmd_pool %p" /*=0xf2f59*/; st[7]=((uintptr_t)&g_hci_cmd_pool) /*=0x20003b4c*/; st[5]=param_1; st[6]=bVar1;
    FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x3080, st);
  }
}

