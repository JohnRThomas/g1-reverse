#include "g1_net_symbols.h"
/* net-core FUN_010091e8 @ 0x10091e8  (parity 300 trials PROVEN) */

static volatile unsigned int * const DAT_010091f4 = (volatile unsigned int *)((uintptr_t)&g_net_addr_record) /*=0x21000a60*/;
unsigned int FUN_010091e8(unsigned int *param_1)
{
  unsigned int v0 = param_1[0];
  unsigned int v1 = param_1[1];
  unsigned int v2 = param_1[2];
  DAT_010091f4[0] = v0;
  DAT_010091f4[1] = v1;
  DAT_010091f4[2] = v2;
  return 0;
}

