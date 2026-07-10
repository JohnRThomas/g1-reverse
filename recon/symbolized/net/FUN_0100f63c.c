#include "g1_net_symbols.h"
/* net-core FUN_0100f63c @ 0x100f63c  (parity 300 trials PROVEN) */

int FUN_0100f63c(void)
{
  volatile unsigned int *p8  = (volatile unsigned int*)((uintptr_t)&g_net_esb_prng_state_hi) /*=0x21000efc*/;
  volatile unsigned int *pc  = (volatile unsigned int*)((uintptr_t)&g_net_esb_prng_state_lo) /*=0x21000f00*/;
  unsigned int uVar2, uVar3, uVar4;

  uVar3 = *p8;
  uVar4 = *pc ^ uVar3;
  uVar2 = uVar3 * 0x9e3779bbu;
  *p8 = uVar4 ^ ((uVar3 >> 6) | (uVar3 << 0x1a)) ^ (uVar4 << 9);
  *pc = (uVar4 >> 0x13) | (uVar4 << 0xd);
  return (int)(((uVar2 >> 0x1b) | (uVar2 << 5)) * 5);
}

