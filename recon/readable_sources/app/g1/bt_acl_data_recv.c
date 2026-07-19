#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_conn__param_0034                    [param_0034; library]
 *   param_2          => struct g1_layout_net_buf__param_0172                    [param_0172; library]
 * Raw function identity: 0x00056394.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00056394 @ 0x00056394
 * public-name: bt_acl_data_recv
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   tx_notify                                <= FUN_00056020 @ 0x00056020
 *   bt_acl_data_recv                         <= FUN_00056394 @ 0x00056394
 *   bt_l2cap_recv                            <= FUN_00057cc4 @ 0x00057cc4
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   bt_conn_call_4arg_zero                   <= FUN_000813ca @ 0x000813ca
 *   bt_conn_reset_rx_state                   <= FUN_000813d6 @ 0x000813d6
 *   net_buf_simple_tailroom                  <= FUN_00083730 @ 0x00083730
 *   net_buf_simple_add_mem                   <= FUN_00083740 @ 0x00083740
 * address symbols (name @ address):
 *   log_module_bt_conn                       @ 0x00088108
 *   rodata_f3b12                             @ 0x000f3b12
 *   rodata_f3b2f                             @ 0x000f3b2f
 *   rodata_f3b4d                             @ 0x000f3b4d
 *   rodata_f3b74                             @ 0x000f3b74
 *   rodata_f3b92                             @ 0x000f3b92
 */
/* Reconstructed FUN_00056394 @ 0x56394  (parity: 300/300 trials, PROVEN) */

extern int tx_notify();
extern int bt_l2cap_recv(int,int,int);
extern int net_buf_unref(int);
extern int bt_conn_call_4arg_zero(int,int,void*);
extern int bt_conn_reset_rx_state(int);
extern int net_buf_simple_tailroom(int);
extern int net_buf_simple_add_mem(int,int,int);

void bt_acl_data_recv(int param_1, int param_2, int param_3)
{
  unsigned short uVar1;
  unsigned int uVar2;
  int iVar3;
  unsigned int local_40;
  unsigned int local_3c;
  unsigned int uStack_38;
  unsigned int local_34;
  int local_20;
  unsigned int local_1c;

  tx_notify();
  if (param_3 == 1) {
    if (*(int*)(param_1+0x10) != 0) {
      uVar1 = *(unsigned short*)(param_2+0x10);
      if (uVar1 != 0) {
        uVar2 = net_buf_simple_tailroom(*(int*)(param_1+0x10)+0xc);
        if (uVar1 <= uVar2) {
          net_buf_simple_add_mem(*(int*)(param_1+0x10)+0xc, *(unsigned int*)(param_2+0xc), *(unsigned short*)(param_2+0x10));
          net_buf_unref(param_2);
          goto control_label_563ce;
        }
        local_1c = ((unsigned long)&rodata_f3b4d) /*=0xf3b4d*/;
        local_20 = 2;
        bt_conn_call_4arg_zero(((unsigned long)&log_module_bt_conn) /*=0x88108*/, 0x1040, &local_20);
        bt_l2cap_recv(param_1, *(unsigned int*)(param_1+0x10), 0);
        *(unsigned int*)(param_1+0x10) = 0;
      }
      goto control_label_56432;
    }
    local_1c = ((unsigned long)&rodata_f3b2f) /*=0xf3b2f*/;
    local_20 = 2;
    bt_conn_call_4arg_zero(((unsigned long)&log_module_bt_conn) /*=0x88108*/, 0x1040, &local_20);
  } else {
    if (param_3 == 2) {
      if (*(int*)(param_1+0x10) != 0) {
        local_1c = ((unsigned long)&rodata_f3b12) /*=0xf3b12*/;
        local_20 = param_3;
        bt_conn_call_4arg_zero(((unsigned long)&log_module_bt_conn) /*=0x88108*/, 0x1040, &local_20);
        bt_conn_reset_rx_state(param_1);
      }
      *(int*)(param_1+0x10) = param_2;
control_label_563ce:
      iVar3 = *(int*)(param_1+0x10);
      uStack_38 = (unsigned int)*(unsigned short*)(iVar3+0x10);
      if (uStack_38 < 2) {
        return;
      }
      local_34 = (unsigned int)(unsigned short)(**(short**)(iVar3+0xc) + 4);
      if (uStack_38 < local_34) {
        return;
      }
      if (local_34 < uStack_38) {
        local_3c = ((unsigned long)&rodata_f3b92) /*=0xf3b92*/;
        local_40 = 4;
        bt_conn_call_4arg_zero(((unsigned long)&log_module_bt_conn) /*=0x88108*/, 0x2040, &local_40);
        bt_conn_reset_rx_state(param_1);
        return;
      }
      *(unsigned int*)(param_1+0x10) = 0;
      bt_l2cap_recv(param_1, iVar3, 1);
      return;
    }
    local_3c = ((unsigned long)&rodata_f3b74) /*=0xf3b74*/;
    local_40 = 3;
    uStack_38 = param_3;
    bt_conn_call_4arg_zero(((unsigned long)&log_module_bt_conn) /*=0x88108*/, 0x1840, &local_40);
  }
  bt_conn_reset_rx_state(param_1);
control_label_56432:
  net_buf_unref(param_2);
  return;
}
