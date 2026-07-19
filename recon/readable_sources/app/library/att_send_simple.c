#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081940 @ 0x00081940
 * public-name: att_send_simple
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   bt_conn_create_pdu                       <= FUN_00081820 @ 0x00081820
 *   att_send_simple                          <= FUN_00081940 @ 0x00081940
 */
/* Reconstructed FUN_00081940 @ 0x81940  (parity: 300/300 trials, PROVEN) */

extern int bt_conn_create_pdu(int a, int b, int c, int d, int e, int f);
extern void net_buf_unref(int a);
void att_send_simple(int param_1, int param_2)
{
  int iVar1;
  iVar1 = bt_conn_create_pdu(param_1, 5, param_2, 0, 0, param_2);
  if (iVar1 != 0) {
    net_buf_unref(param_2);
  }
}
