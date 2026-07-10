/* named: att_send_simple */
/* Reconstructed att_send_simple @ 0x81940  (parity: 300/300 trials, PROVEN) */

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

