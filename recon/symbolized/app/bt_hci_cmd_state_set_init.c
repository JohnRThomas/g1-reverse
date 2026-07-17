#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00053cb0 @ 0x00053cb0
 * public-name: bt_hci_cmd_state_set_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_state_set_init                <= FUN_00053cb0 @ 0x00053cb0
 *   net_buf_id                               <= FUN_0005ee18 @ 0x0005ee18
 * address symbols (name @ address):
 *   bt_hci_cmd_data                          @ 0x2000abf4
 */
/* Reconstructed FUN_00053cb0 @ 0x53cb0  (parity: 300/300 trials, PROVEN) */

extern int net_buf_id(void);

void bt_hci_cmd_state_set_init(unsigned int param_1, unsigned int *param_2, unsigned int param_3, unsigned int param_4, unsigned char param_5)
{
  int iVar1;

  param_2[0] = param_3;
  param_2[1] = param_4;
  *(unsigned char *)(param_2 + 2) = param_5;
  iVar1 = net_buf_id();
  *(unsigned int **)(iVar1 * 0xc + ((unsigned long)&bt_hci_cmd_data) /*=0x2000abf4*/ + 4) = param_2;
  return;
}
