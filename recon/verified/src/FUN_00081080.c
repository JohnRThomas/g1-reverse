/* Reconstructed FUN_00081080 @ 0x81080  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_000812d2(int, uint32_t);

void FUN_00081080(int param_1)
{
  volatile uint32_t *p = (volatile uint32_t*)(param_1 + 0x10);
  uint32_t uVar1 = *p;
  *p = uVar1 & 0xffff7fffUL;
  if ((int32_t)(uVar1 << 0x10) < 0) {
    FUN_000812d2(param_1, 1);
  }
}

