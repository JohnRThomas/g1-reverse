#include "g1_app_symbols.h"
/* named: smp_dhkey_generate */
/* Reconstructed smp_dhkey_generate @ 0x5cc68  (parity: 300/300 trials, PROVEN) */

extern void atomic_set_bit(int a, int b);
extern int FUN_00055e74(int a, int b);
extern void atomic_clear_bit_1(int a, int b);
extern void FUN_00083074(int a, int b, void *c);

int smp_dhkey_generate(int param_1)
{
  int iVar1;
  unsigned int local_18;
  unsigned int local_14;

  atomic_set_bit(param_1 + 4, 8);
  iVar1 = FUN_00055e74(param_1 + 0x57, ((uintptr_t)&rodata_8349d) /*=0x8349d*/);
  if (iVar1 != 0) {
    atomic_clear_bit_1(param_1 + 4, 8);
    local_14 = "Failed to generate DHKey" /*=0xf4e47*/;
    local_18 = 2;
    FUN_00083074(((uintptr_t)&tbl_880d8) /*=0x88180*/, 0x1040, &local_18);
    iVar1 = 8;
  }
  return iVar1;
}

