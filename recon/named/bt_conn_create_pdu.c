/* named: bt_conn_create_pdu */
/* Reconstructed bt_conn_create_pdu @ 0x81820  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern short* net_buf_simple_push(int,int);
extern unsigned FUN_000564cc(int,int,int,unsigned);

unsigned bt_conn_create_pdu(int param_1, short param_2, int param_3, int param_4, unsigned param_5){
  short *psVar4 = net_buf_simple_push(param_3 + 0xc, 4);
  short sVar1 = *(short*)(param_3 + 0x10);
  psVar4[1] = param_2;
  *psVar4 = (short)(sVar1 - 4);
  return FUN_000564cc(param_1, param_3, param_4, param_5);
}

