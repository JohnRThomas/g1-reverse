#include "g1_app_symbols.h"
/* named: FUN_000850f6 */
/* Reconstructed FUN_000850f6 @ 0x850f6  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_000850f6(unsigned int param_1)
{
  unsigned int uVar1;
  if ((param_1 >> 5) == 0) {
    uVar1 = 0xffffffff;
  } else {
    if ((param_1 >> 5) != 1) {
      return 0;
    }
    uVar1 = ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
  }
  return (uVar1 >> (param_1 & 0x1f)) & 1;
}

