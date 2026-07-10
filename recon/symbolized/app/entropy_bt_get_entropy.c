#include "g1_app_symbols.h"
/* named: entropy_bt_get_entropy */
/* Reconstructed entropy_bt_get_entropy @ 0x83896  (parity: 300/300 trials, PROVEN) */

extern int bt_is_ready(void);
extern unsigned int bt_hci_le_rand(unsigned int, unsigned int);

unsigned int entropy_bt_get_entropy(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;
  unsigned int uVar2;

  iVar1 = bt_is_ready();
  if (iVar1 != 0) {
    uVar2 = bt_hci_le_rand(param_2,param_3);
    return uVar2;
  }
  return 0xfffffff5;
}

