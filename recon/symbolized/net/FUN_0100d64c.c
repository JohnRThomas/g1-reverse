#include "g1_net_symbols.h"
/* net-core FUN_0100d64c @ 0x100d64c  (parity 300 trials PROVEN) */

unsigned int FUN_0100d64c(unsigned int param_1, unsigned int param_2)
{
  unsigned long long r;
  if (param_2 > 0x1d4b) {
    r = (unsigned long long)0xd1b71759u * (unsigned long long)param_1;
    return (unsigned int)((r >> 32) >> 10) & 0xff;
  }
  r = (unsigned long long)0x51eb851fu * (unsigned long long)param_1;
  return (unsigned int)((r >> 32) >> 5) & 0xff;
}
