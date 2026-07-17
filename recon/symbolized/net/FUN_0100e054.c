#include "g1_net_symbols.h"
/* net-core FUN_0100e054 @ 0x100e054  (parity 300 trials PROVEN) */

void FUN_0100e054(unsigned char *param_1, unsigned int param_2)
{
  unsigned int v = (*param_1 & 0x7f) | (param_2 << 7);
  *param_1 = (unsigned char)v;
}
