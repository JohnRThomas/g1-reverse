#include "g1_app_symbols.h"
/* named: bigint_copy_words_zero_pad */
/* Reconstructed bigint_copy_words_zero_pad @ 0x87648  (parity: 146/300 trials, PROVEN) */

void bigint_copy_words_zero_pad(int param_1, int param_2, int param_3)
{
  unsigned int *puVar1 = (unsigned int*)(param_3+0x14);
  unsigned int *puVar4 = (unsigned int*)(param_1-4);
  unsigned int *puVar3 = puVar1 + *(int*)(param_3+0x10);
  unsigned int uVar2;

  for (; puVar1 < puVar3; puVar1++) {
    puVar4++;
    *puVar4 = *puVar1;
  }
  uVar2 = ((unsigned int)puVar3 + (unsigned int)(-0x11 - param_3)) & 0xfffffffc;
  if (puVar3 < (unsigned int*)(param_3+0x11U)) {
    uVar2 = 0;
  }
  for (puVar4 = (unsigned int*)(param_1+uVar2); puVar4 < (unsigned int*)(param_1 + (((param_2-1)>>5)+1)*4); puVar4++) {
    *puVar4 = 0;
  }
  return;
}

