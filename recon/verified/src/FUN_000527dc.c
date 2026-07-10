/* Reconstructed FUN_000527dc @ 0x527dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int* FUN_000527dc(int param_1)
{
  volatile int *p = (volatile int*)0x20005cb0UL;
  if (*p != param_1) {
    return (int*)0;
  }
  return (int*)p;
}

