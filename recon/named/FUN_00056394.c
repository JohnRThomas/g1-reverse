/* named: FUN_00056394 */
/* globals referenced:
//   0x00088108  log_module_bt_conn           
*/
/* Reconstructed FUN_00056394 @ 0x56394  (parity: 300/300 trials, PROVEN) */

extern int tx_notify();
extern int bt_l2cap_recv(int,int,int);
extern int net_buf_unref(int);
extern int FUN_000813ca(int,int,void*);
extern int bt_conn_reset_rx_state(int);
extern int net_buf_simple_tailroom(int);
extern int net_buf_simple_push_mem(int,int,int);

void FUN_00056394(int param_1, int param_2, int param_3)
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
          net_buf_simple_push_mem(*(int*)(param_1+0x10)+0xc, *(unsigned int*)(param_2+0xc), *(unsigned short*)(param_2+0x10));
          net_buf_unref(param_2);
          goto LAB_563ce;
        }
        local_1c = 0xf3b4d;
        local_20 = 2;
        FUN_000813ca(0x88108, 0x1040, &local_20);
        bt_l2cap_recv(param_1, *(unsigned int*)(param_1+0x10), 0);
        *(unsigned int*)(param_1+0x10) = 0;
      }
      goto LAB_56432;
    }
    local_1c = 0xf3b2f;
    local_20 = 2;
    FUN_000813ca(0x88108, 0x1040, &local_20);
  } else {
    if (param_3 == 2) {
      if (*(int*)(param_1+0x10) != 0) {
        local_1c = 0xf3b12;
        local_20 = param_3;
        FUN_000813ca(0x88108, 0x1040, &local_20);
        bt_conn_reset_rx_state(param_1);
      }
      *(int*)(param_1+0x10) = param_2;
LAB_563ce:
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
        local_3c = 0xf3b92;
        local_40 = 4;
        FUN_000813ca(0x88108, 0x2040, &local_40);
        bt_conn_reset_rx_state(param_1);
        return;
      }
      *(unsigned int*)(param_1+0x10) = 0;
      bt_l2cap_recv(param_1, iVar3, 1);
      return;
    }
    local_3c = 0xf3b74;
    local_40 = 3;
    uStack_38 = param_3;
    FUN_000813ca(0x88108, 0x1840, &local_40);
  }
  bt_conn_reset_rx_state(param_1);
LAB_56432:
  net_buf_unref(param_2);
  return;
}

