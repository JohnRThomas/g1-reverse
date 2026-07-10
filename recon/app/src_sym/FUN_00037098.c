/* Reconstructed FUN_00037098 @ 0x37098  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_0001672c(void);
void FUN_00037098(void)
{
  *(volatile uint8_t*)(0x20004950UL + 1) = 0;
  *(volatile uint8_t*)0x2001b816UL = 0;
  FUN_0001672c();
  return;
}

