#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00058c34 @ 0x00058c34
 * public-name: gatt_notify_or_indicate
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_chan_req_free                        <= FUN_0005833c @ 0x0005833c
 *   bt_att_chan_create_pdu                   <= FUN_000585f0 @ 0x000585f0
 *   gatt_notify_or_indicate                  <= FUN_00058c34 @ 0x00058c34
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   bt_gatt_foreach_attr                     <= FUN_00081cee @ 0x00081cee
 *   bt_att_chan_send_rsp                     <= FUN_000821a4 @ 0x000821a4
 *   att_send_error_rsp                       <= FUN_000821f4 @ 0x000821f4
 *   atomic_test_and_set_bit_0                <= FUN_00082236 @ 0x00082236
 *   bt_gatt_change_aware                     <= FUN_00082ec8 @ 0x00082ec8
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   ADDR_FUN_00081c8c_THUMB                  @ 0x00081c8d
 */
/* Reconstructed FUN_00058c34 @ 0x58c34  (parity: 300/300 trials, PROVEN) */
extern int att_chan_req_free(int);
extern int bt_att_chan_create_pdu(void*,int,int);
extern void net_buf_unref(int);
extern void bt_gatt_foreach_attr(int,int,int,void*);
extern void bt_att_chan_send_rsp(void*);
extern void att_send_error_rsp(void*,int,int,int);
extern int atomic_test_and_set_bit_0(void*,int);
extern int bt_gatt_change_aware(int,int);
extern void memset_bytes(void*,int,int);
char gatt_notify_or_indicate(int *param_1,int param_2,int param_3,int param_4,short param_5,int param_6,short param_7){
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
    bt_gatt_foreach_attr(param_4, param_4, ADDR_FUN_00081c8c_THUMB /*=0x81c8d*/, &S);
    if (S.g == 0){
      if (local_2c != 0) bt_att_chan_send_rsp(param_1);
      return 0;
    } else {
      if (param_3 != 0){
        att_chan_req_free(*(int*)(local_2c + 0x18));
        net_buf_unref(local_2c);
        att_send_error_rsp(param_1, param_2, param_4, S.g);
      }
      if (param_2 == 0x18) return S.g;
    }
  }
  return 0;
}
