#include "g1_net_symbols.h"
/* net-core FUN_01031804 @ 0x1031804  (parity 300 trials PROVEN) */

extern void FUN_01036410(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
void FUN_01031804(unsigned int param_1, unsigned int param_2)
{
  FUN_01036410(((uintptr_t)&g_net_fatal_halt_sem) /*=0x210008cc*/, param_2, param_1, param_2);
}

