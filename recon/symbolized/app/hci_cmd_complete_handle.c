#include "g1_app_symbols.h"
struct k_sem;
/* readable reconstruction; identity: FUN_000538f8 @ 0x000538f8
 * public-name: hci_cmd_complete_handle
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   hci_cmd_complete_handle                  <= FUN_000538f8 @ 0x000538f8
 *   net_buf_pool_get                         <= FUN_0005ee08 @ 0x0005ee08
 *   net_buf_id                               <= FUN_0005ee18 @ 0x0005ee18
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   atomic_or                                <= FUN_00080e6a @ 0x00080e6a
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 *   atomic_and_3                             <= FUN_00080ea8 @ 0x00080ea8
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f2f59                             @ 0x000f2f59
 *   rodata_f2f8e                             @ 0x000f2f8e
 *   g_ble_dev_state                          @ 0x20002000
 *   g_hci_cmd_pool                           @ 0x20003b4c
 *   bt_hci_cmd_data                          @ 0x2000abf4
 */
/* Reconstructed FUN_000538f8 @ 0x538f8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int net_buf_pool_get(unsigned);
extern int net_buf_id(int);
extern void net_buf_unref(void);
extern void k_sem_give(struct k_sem *);
extern void atomic_or(int);
extern void bt_log_forward_3arg(unsigned,unsigned,void*);
extern long atomic_and_3(volatile long*, long);

void hci_cmd_complete_handle(unsigned param_1, int param_2, int param_3, unsigned param_4){
  int iVar3 = net_buf_pool_get(*(unsigned char*)(param_3 + 10));
  if(*(volatile int*)((unsigned long)&g_hci_cmd_pool) /*=0x20003b4c*/ == iVar3){
    int iVar4 = net_buf_id(param_3);
    if(*(volatile unsigned short*)(iVar4*0xc + ((unsigned long)&bt_hci_cmd_data) /*=0x2000abf4*/ + 2) == (unsigned short)param_1){
      if(*(volatile int*)(((unsigned long)&g_ble_dev_state) /*=0x20002000*/ + 0x140) != 0){
        net_buf_unref();
        *(volatile int*)(((unsigned long)&g_ble_dev_state) /*=0x20002000*/ + 0x140) = 0;
      }
      {
        int i = net_buf_id(param_3);
        if(*(volatile int*)(i*0xc + ((unsigned long)&bt_hci_cmd_data) /*=0x2000abf4*/ + 4) != 0 && param_2 == 0){
          int j = net_buf_id(param_3);
          int *piVar5 = *(int* volatile*)(j*0xc + ((unsigned long)&bt_hci_cmd_data) /*=0x2000abf4*/ + 4);
          unsigned uVar6 = (unsigned)piVar5[1] >> 5;
          if((char)piVar5[2] == 0)
            atomic_and_3(piVar5[0] + uVar6*4, ~(1 << (piVar5[1] & 0x1f)));
          else
            atomic_or(piVar5[0] + uVar6*4);
        }
      }
      {
        int k = net_buf_id(param_3);
        if(*(volatile int*)(k*0xc + ((unsigned long)&bt_hci_cmd_data) /*=0x2000abf4*/ + 8) != 0){
          int m = net_buf_id(param_3);
          *(volatile char*)(((unsigned long)&bt_hci_cmd_data) /*=0x2000abf4*/ + m*0xc) = (char)param_2;
          int n = net_buf_id(param_3);
          k_sem_give(*(volatile unsigned*)(n*0xc + ((unsigned long)&bt_hci_cmd_data) /*=0x2000abf4*/ + 8));
        }
      }
    } else {
      int i = net_buf_id(param_3);
      unsigned st[8];
      st[0]=4; st[3]=((unsigned long)&rodata_f2f8e) /*=0xf2f8e*/; st[4]=param_1; st[7]=*(volatile unsigned short*)(i*0xc + ((unsigned long)&bt_hci_cmd_data) /*=0x2000abf4*/ + 2);
      bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x2080, st);
    }
  } else {
    unsigned char bVar1 = *(unsigned char*)(param_3 + 10);
    unsigned st[8];
    st[2] = net_buf_pool_get((unsigned)bVar1);
    st[0]=6; st[1]=((unsigned long)&rodata_f2f59) /*=0xf2f59*/; st[7]=((unsigned long)&g_hci_cmd_pool) /*=0x20003b4c*/; st[5]=param_1; st[6]=bVar1;
    bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x3080, st);
  }
}
