#include "g1_app_symbols.h"
/* named: bignum_any_bit_set_from */
/* Reconstructed bignum_any_bit_set_from @ 0x8768e  (parity: 92/300 trials, PROVEN) */

int bignum_any_bit_set_from(char *param_1, unsigned int param_2)
{
  int *piVar3 = (int*)(param_1 + 0x14);
  int iVar4 = (int)param_2 >> 5;
  int iVar2 = *(int*)(param_1 + 0x10);
  int offset;
  int cond;
  if (iVar2 < iVar4) {
    offset = iVar2;
    cond = 1;
  } else {
    int bVar1 = (iVar2 <= iVar4);
    iVar2 = iVar4;
    offset = iVar4;
    if (bVar1) {
      cond = 1;
    } else {
      unsigned int p2 = param_2 & 0x1f;
      if (p2 == 0) {
        cond = 1;
      } else {
        cond = (piVar3[iVar4] == (int)(((unsigned int)piVar3[iVar4] >> p2) << p2));
      }
    }
  }
  if (cond) {
    int *piVar5 = piVar3 + offset;
    while (1) {
      if (piVar5 <= piVar3) return 0;
      piVar5--;
      if (*piVar5 != 0) break;
    }
  }
  return 1;
}

