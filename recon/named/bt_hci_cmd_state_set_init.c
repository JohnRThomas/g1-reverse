/* named: bt_hci_cmd_state_set_init */
/* Reconstructed bt_hci_cmd_state_set_init @ 0x53cb0  (parity: 300/300 trials, PROVEN) */

extern int net_buf_id(void);

void bt_hci_cmd_state_set_init(unsigned int param_1, unsigned int *param_2, unsigned int param_3, unsigned int param_4, unsigned char param_5)
{
  int iVar1;

  param_2[0] = param_3;
  param_2[1] = param_4;
  *(unsigned char *)(param_2 + 2) = param_5;
  iVar1 = net_buf_id();
  *(unsigned int **)(iVar1 * 0xc + 0x2000abf4UL + 4) = param_2;
  return;
}

