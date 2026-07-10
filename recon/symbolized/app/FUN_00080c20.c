#include "g1_app_symbols.h"
/* named: FUN_00080c20 */
/* Reconstructed FUN_00080c20 @ 0x80c20  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_000527dc(unsigned int a);

unsigned int FUN_00080c20(int param_1, unsigned int param_2)
{
  unsigned long long uVar1;
  if (param_2 != 0) {
    uVar1 = FUN_000527dc(param_2);
    param_2 = (unsigned int)uVar1;
    if (param_2 != 0) {
      if (*(int*)(param_1+0x18) == (int)(uVar1>>32)) {
        param_2 = (unsigned int)(*(char*)(param_2+0x69) == *(char*)(param_1+0x1c));
      } else {
        param_2 = 1;
      }
    }
  }
  return param_2;
}

