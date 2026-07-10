#include "g1_app_symbols.h"
/* named: attr_configure_mode3_readback */
/* Reconstructed attr_configure_mode3_readback @ 0x7d05e  (parity: 300/300 trials, PROVEN) */

extern int attr_store_set(unsigned int a, unsigned int b);
extern int attr_store_get(unsigned int a, unsigned int b);
extern int wait_attr_0x4714_clear(void);

int attr_configure_mode3_readback(unsigned int param_1)
{
  int iVar1;

  iVar1 = attr_store_set(0x4704, 0);
  if ((((iVar1 == 0) && (iVar1 = attr_store_set(0x4710,3), iVar1 == 0)) &&
      (iVar1 = attr_store_set(0x4714,1), iVar1 == 0)) && (iVar1 = wait_attr_0x4714_clear(), iVar1 == 0)) {
    iVar1 = attr_store_get(0x470c,param_1);
    if (iVar1 != 0) {
      iVar1 = 1;
    }
    iVar1 = -iVar1;
  } else {
    iVar1 = -1;
  }
  return iVar1;
}

