#include "g1_app_symbols.h"
/* named: max_utilization_update */
/* Reconstructed max_utilization_update @ 0x7e4f2  (parity: 300/300 trials, PROVEN) */

extern unsigned int get_usage(void);
void max_utilization_update(int param_1)
{
  unsigned int uVar1;
  unsigned int uVar2;
  if ((*(volatile int *)(param_1 + 0x10) << 0x1d) < 0) {
    uVar2 = *(volatile unsigned int *)(param_1 + 0x28);
    uVar1 = get_usage();
    if (uVar1 <= uVar2) {
      *(volatile unsigned int *)(param_1 + 0x28) = uVar2;
    }
    if (uVar1 > uVar2) {
      *(volatile unsigned int *)(param_1 + 0x28) = uVar1;
    }
  }
}

