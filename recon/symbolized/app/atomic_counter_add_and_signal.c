#include "g1_app_symbols.h"
/* named: atomic_counter_add_and_signal */
/* Reconstructed atomic_counter_add_and_signal @ 0x8174c  (parity: 300/300 trials, PROVEN) */

void atomic_counter_add_and_signal(int param_1, int param_2)
{
  unsigned int uVar1;
  *(volatile int*)(param_1+0x2c) = *(volatile int*)(param_1+0x2c) + param_2;
  uVar1 = *(volatile unsigned int*)(param_1+0x10);
  *(volatile unsigned int*)(param_1+0x10) = uVar1 | 1;
  if ((uVar1 & 1) == 0) {
    void (*fn)(void) = *(void (**)(void))(*(volatile int*)(param_1+4) + 0x1c);
    if (fn != 0) {
      fn();
    }
  }
}

