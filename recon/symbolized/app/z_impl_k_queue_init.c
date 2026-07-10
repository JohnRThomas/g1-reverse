#include "g1_app_symbols.h"
/* named: z_impl_k_queue_init */
/* Reconstructed z_impl_k_queue_init @ 0x864e8  (parity: 300/300 trials, PROVEN) */

void z_impl_k_queue_init(int *param_1)
{
  *(volatile unsigned int *)(param_1) = 0;
  *(volatile unsigned int *)((int)param_1+4) = 0;
  *(volatile unsigned int *)((int)param_1+8) = 0;
  *(volatile unsigned int *)((int)param_1+0xc) = (unsigned int)param_1 + 0xc;
  *(volatile unsigned int *)((int)param_1+0x10) = (unsigned int)param_1 + 0xc;
  *(volatile unsigned int *)((int)param_1+0x14) = (unsigned int)param_1 + 0x14;
  *(volatile unsigned int *)((int)param_1+0x18) = (unsigned int)param_1 + 0x14;
}

