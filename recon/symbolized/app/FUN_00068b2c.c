#include "g1_app_symbols.h"
/* named: FUN_00068b2c */
/* Reconstructed FUN_00068b2c @ 0x68b2c  (parity: 300/300 trials, PROVEN) */

extern void lc3_bits_accu_flush(void);
void FUN_00068b2c(int param_1, unsigned int param_2, int param_3)
{
  unsigned int uVar1;
  int iVar2;
  uVar1 = (param_2 > 1) ? 1 : 0;
  if (param_2 != 0) uVar1 += 1;
  if (param_2 > 3) uVar1 += 1;
  if (uVar1 != 0) {
    iVar2 = uVar1 + *(unsigned int*)(param_1+0x20);
    if (iVar2 > 0x20) {
      lc3_bits_accu_flush();
      return;
    }
    *(unsigned int*)(param_1+0x1c) = *(unsigned int*)(param_1+0x1c) | (param_3 << (*(unsigned int*)(param_1+0x20) & 0xff));
    *(int*)(param_1+0x20) = iVar2;
  }
}

