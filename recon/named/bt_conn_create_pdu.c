/* readable reconstruction; identity: FUN_00081820 @ 0x00081820
 * public-name: bt_conn_create_pdu
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_send_cb                          <= FUN_000564cc @ 0x000564cc
 *   net_buf_simple_push                      <= FUN_0005f518 @ 0x0005f518
 *   bt_conn_create_pdu                       <= FUN_00081820 @ 0x00081820
 */
/* Reconstructed FUN_00081820 @ 0x81820.
 * Complete 50-byte tail-dispatch wrapper; 0x81852 starts the next function. */
#include <stdint.h>
extern short* net_buf_simple_push(int,int);
extern unsigned bt_conn_send_cb(int,int,int,unsigned);

unsigned bt_conn_create_pdu(int param_1, short param_2, int param_3, int param_4, unsigned param_5){
  short *psVar4 = net_buf_simple_push(param_3 + 0xc, 4);
  short sVar1 = *(short*)(param_3 + 0x10);
  psVar4[1] = param_2;
  *psVar4 = (short)(sVar1 - 4);
  return bt_conn_send_cb(param_1, param_3, param_4, param_5);
}
