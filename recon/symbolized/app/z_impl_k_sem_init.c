#include "g1_app_symbols.h"
/* named: z_impl_k_sem_init */
/* Reconstructed z_impl_k_sem_init @ 0x86534  (parity: 300/300 trials, PROVEN) */

unsigned int z_impl_k_sem_init(int param_1, unsigned int param_2, unsigned int param_3)
{
  if ((param_3 != 0) && (param_2 <= param_3)) {
    *(unsigned int *)(param_1 + 8) = param_2;
    *(unsigned int *)(param_1 + 0xc) = param_3;
    *(int *)param_1 = param_1;
    *(int *)(param_1 + 4) = param_1;
    *(int *)(param_1 + 0x10) = param_1 + 0x10;
    *(int *)(param_1 + 0x14) = param_1 + 0x10;
    return 0;
  }
  return 0xffffffea;
}

