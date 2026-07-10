#include "g1_app_symbols.h"
/* named: attr_configure_pair */
/* Reconstructed attr_configure_pair @ 0x7cfdc  (parity: 300/300 trials, PROVEN) */

extern int attr_store_set(unsigned int a, unsigned int b);
extern int wait_attr_0x4714_clear(void);

int attr_configure_pair(unsigned int param_1, unsigned int param_2)
{
  int iVar1;

  iVar1 = attr_store_set(0x4704,param_1);
  if ((((iVar1 == 0) && (iVar1 = attr_store_set(0x4708,param_2), iVar1 == 0)) &&
      (iVar1 = attr_store_set(0x4710,0xc), iVar1 == 0)) &&
     (iVar1 = attr_store_set(0x4714,1), iVar1 == 0)) {
    iVar1 = wait_attr_0x4714_clear();
    if (iVar1 != 0) {
      iVar1 = 1;
    }
    iVar1 = -iVar1;
  } else {
    iVar1 = -1;
  }
  return iVar1;
}

