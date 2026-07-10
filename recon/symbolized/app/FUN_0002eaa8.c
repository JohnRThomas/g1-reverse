#include "g1_app_symbols.h"
/* named: FUN_0002eaa8 */
/* Reconstructed FUN_0002eaa8 @ 0x2eaa8  (parity: 300/300 trials, PROVEN) */

extern int dev_write_reg3(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern void DEBUG_PRINT(unsigned int a0);

unsigned int FUN_0002eaa8(void)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int base = *(volatile unsigned int*)(((uintptr_t)&tbl_87c80) /*=0x87ce0*/ + 4);
  iVar1 = dev_write_reg3(*(volatile unsigned int*)(base + 0x1c), 3, 4, 1);
  if (iVar1 < 0) {
    DEBUG_PRINT("Could not enable charger\n" /*=0xa3e48*/);
    uVar2 = 0xffffffff;
  } else {
    uVar2 = 0;
  }
  return uVar2;
}

