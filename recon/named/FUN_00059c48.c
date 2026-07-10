/* named: FUN_00059c48 */
/* Reconstructed FUN_00059c48 @ 0x59c48  (parity: 300/300 trials, PROVEN) */

extern int bt_conn_is_peer_addr_le(int a, unsigned char b);
extern int bt_addr_le_eq_0(unsigned char *a, int b);
unsigned char *FUN_00059c48(int param_1, unsigned char *param_2)
{
  int iVar1;

  if (param_1 == 0) {
    iVar1 = bt_addr_le_eq_0(param_2 + 1, 0x000f2b3a);
  } else {
    iVar1 = bt_conn_is_peer_addr_le(param_1, *param_2);
  }
  if (iVar1 == 0) {
    param_2 = (unsigned char *)0;
  }
  return param_2;
}

