#include "g1_app_symbols.h"
/* named: index_in_range32_mask */
/* Reconstructed index_in_range32_mask @ 0x7d860  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int index_in_range32_mask(unsigned int param_1)
{
  unsigned int uVar1;
  uVar1 = 0xffffffff;
  if (0x1f < param_1) {
    uVar1 = 0;
  }
  return uVar1;
}

