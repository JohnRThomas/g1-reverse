#include "g1_net_symbols.h"
/* net-core FUN_0100930c @ 0x100930c  (parity 300 trials PROVEN) */

unsigned int FUN_0100930c(unsigned int param_1)
{
  int iVar1;
  if (param_1 < 0x40) {
    param_1 = param_1 - 1;
    iVar1 = 0x21000000;
  } else {
    if (param_1 == 0xff) return 1;
    param_1 = param_1 - 0x40;
    iVar1 = 0x21000b70;
  }
  return (*(unsigned int*)(iVar1 + ((int)(param_1 * 0x1000000) >> 0x1d) * 4) >> (param_1 & 0x1f)) & 1;
}
