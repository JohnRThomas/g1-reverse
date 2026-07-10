#include "g1_net_symbols.h"
/* net-core FUN_01013e98 @ 0x1013e98  (parity 300 trials PROVEN) */

extern void FUN_01013e98_tail(unsigned int a);

void FUN_01013e98(unsigned char *param_1, unsigned int param_2)
{
  if (param_2 == 2) {
    param_1[0x31c] = 4;
  }
  FUN_01013e98_tail(param_2);
}

