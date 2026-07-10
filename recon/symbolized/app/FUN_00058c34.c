#include "g1_app_symbols.h"
/* named: FUN_00058c34 */
/* Reconstructed FUN_00058c34 @ 0x58c34  (parity: 300/300 trials, PROVEN) */
extern int FUN_0005833c(int);
extern int bt_att_chan_create_pdu(void*,int,int);
extern void net_buf_unref(int);
extern void bt_gatt_foreach_attr(int,int,int,void*);
extern void bt_att_chan_send_rsp(void*);
extern void att_send_error_rsp(void*,int,int,int);
extern int atomic_test_and_set_bit_0(void*,int);
extern int bt_gatt_change_aware(int,int);
extern void memset_bytes(void*,int,int);
char FUN_00058c34(int *param_1,int param_2,int param_3,int param_4,short param_5,int param_6,short param_7){
  int iVar1 = param_2 ? 1 : 0;
  iVar1 = bt_gatt_change_aware(*(int*)*param_1, iVar1);
  if (iVar1 == 0){
    if (atomic_test_and_set_bit_0((char*)param_1 + 0x120, 5) == 0) return 0x12;
    return 0;
  }
  if (param_4 == 0) return 1;
  {
    struct { int a; int b; unsigned char c; int d; short e; short f; char g; } S;
    int local_2c = 0;
    memset_bytes(&S, 0, 0x18);
    if (param_3 != 0){
      local_2c = bt_att_chan_create_pdu(param_1, param_3, 0);
      if (local_2c == 0) return 0x11;
    }
    S.a = *(int*)*param_1;
    S.f = param_5;
    S.c = (unsigned char)param_2;
    S.d = param_6;
    S.e = param_7;
    S.g = 1;
    bt_gatt_foreach_attr(param_4, param_4, ((uintptr_t)&rodata_81c8d) /*=0x81c8d*/, &S);
    if (S.g == 0){
      if (local_2c != 0) bt_att_chan_send_rsp(param_1);
      return 0;
    } else {
      if (param_3 != 0){
        FUN_0005833c(*(int*)(local_2c + 0x18));
        net_buf_unref(local_2c);
        att_send_error_rsp(param_1, param_2, param_4, S.g);
      }
      if (param_2 == 0x18) return S.g;
    }
  }
  return 0;
}

