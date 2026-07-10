#include "g1_app_symbols.h"
/* named: atomic_set */
/* Reconstructed atomic_set @ 0x2f910  (parity: 300/300 trials, PROVEN) */

unsigned int atomic_set(unsigned int param_1)
{
  volatile unsigned int *p = (volatile unsigned int *)((uintptr_t)&g_atomic_scratch_20007bb0) /*=0x20007bb0*/;
  unsigned int old = *p;
  *p = param_1;
  return old;
}

