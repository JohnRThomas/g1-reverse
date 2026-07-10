#include "g1_app_symbols.h"
/* named: bignum_limbs_merge_shift_left */
/* Reconstructed bignum_limbs_merge_shift_left @ 0x8736a  (parity: 300/300 trials, PROVEN) */

void bignum_limbs_merge_shift_left(unsigned int *param_1, unsigned int *param_2, int param_3)
{
  unsigned int *puVar1;
  unsigned int lshift = (unsigned int)(((8 - param_3) * -4) + 0x20) & 0xff;
  unsigned int rshift = (unsigned int)((8 - param_3) * 4) & 0xff;
  do {
    puVar1 = param_1 + 1;
    *param_1 = *param_1 | (*puVar1 << lshift);
    param_1 = param_1 + 1;
    *param_1 = *puVar1 >> rshift;
  } while (param_1 < param_2);
}

