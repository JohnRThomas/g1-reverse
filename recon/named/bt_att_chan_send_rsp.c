/* named: bt_att_chan_send_rsp */
/* Reconstructed bt_att_chan_send_rsp @ 0x821a4  (parity: 300/300 trials, PROVEN) */

extern int FUN_00058a54(void);
extern void net_buf_destroy_default(unsigned int,unsigned int,unsigned int,unsigned int);
void bt_att_chan_send_rsp(int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  int iVar1 = FUN_00058a54();
  if (iVar1 != 0) {
    net_buf_destroy_default(param_1 + 0x128, param_2, param_3, param_4);
  }
}

