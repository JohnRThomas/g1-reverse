#include "g1_app_symbols.h"
/* named: smp_dhkey_ready_no_context */
/* Reconstructed smp_dhkey_ready_no_context @ 0x5cbe0  (parity: 300/300 trials, PROVEN) */

extern void FUN_00083074(unsigned int a0, unsigned int a1, void *a2);

unsigned int smp_dhkey_ready_no_context(unsigned int param_1)
{
  unsigned int local[3];
  local[0] = 3;
  local[1] = "No available SMP context for conn %p" /*=0xf4e22*/;
  local[2] = param_1;
  FUN_00083074(((uintptr_t)&tbl_880d8) /*=0x88180*/, 0x1840, local);
  return 0xfffffff4;
}

