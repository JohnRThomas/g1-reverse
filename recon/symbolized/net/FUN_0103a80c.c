#include "g1_net_symbols.h"
/* net-core FUN_0103a80c @ 0x103a80c  (parity 300 trials PROVEN) */

unsigned int FUN_0103a80c(unsigned int *param_1)
{
  unsigned int uVar1, val;

  val = *param_1;
  uVar1 = ((val >> 4) & 0x0f0f0f0fu) | ((val << 4) & 0xf0f0f0f0u);
  uVar1 = ((uVar1 >> 2) & 0x33333333u) | ((uVar1 << 2) & 0xccccccccu);
  return ((uVar1 >> 1) & 0x55555555u) | ((uVar1 << 1) & 0xaaaaaaaau);
}
