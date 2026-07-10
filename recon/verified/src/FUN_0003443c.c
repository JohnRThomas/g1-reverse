/* Reconstructed FUN_0003443c @ 0x3443c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_0003441c(void);
void FUN_0003443c(int param_1)
{
  *(volatile uint8_t*)0x2001a229UL = (uint8_t)param_1;
  if (param_1 == 0) {
    FUN_0003441c();
    return;
  }
  return;
}

