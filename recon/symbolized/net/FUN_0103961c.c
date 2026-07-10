#include "g1_net_symbols.h"
/* net-core FUN_0103961c @ 0x103961c  (parity 300 trials PROVEN) */

extern void FUN_0100823c(int a, int b, int c, int d);
extern void FUN_01037c64(void);

void FUN_0103961c(int param_1)
{
  FUN_0100823c(999 + (param_1 << 15), param_1 >> 17, 1000, 0);
  FUN_01037c64();
  return;
}

