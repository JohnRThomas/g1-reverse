#include "g1_app_symbols.h"
/* named: ccc_find_cfg */
/* Reconstructed ccc_find_cfg @ 0x826c2  (parity: 300/300 trials, PROVEN) */

extern int bt_addr_le_eq_0(unsigned char *);

unsigned char * ccc_find_cfg(unsigned char *param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;

  if (*param_1 == param_3) {
    iVar1 = bt_addr_le_eq_0(param_1 + 1);
    if (iVar1 == 0) {
      param_1 = (unsigned char *)0x0;
    }
  }
  else {
    param_1 = (unsigned char *)0x0;
  }
  return param_1;
}

