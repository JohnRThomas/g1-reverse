/* Reconstructed FUN_000651d8 @ 0x651d8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_0007e2fa(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void FUN_0007e2ec(unsigned int, unsigned int);
extern int FUN_000500f0(int);
extern void FUN_000500ac(int);

void FUN_000651d8(void)
{
  if (*(volatile char*)(0x2000b31cUL + 4) == 0) {
    FUN_0007e2fa(0x99cbd, 0xf6acd, 0xf6a4e, 0x12e, 0);
    FUN_0007e2ec(0xf6a4e, 0x12e);
  }
  int iVar1 = FUN_000500f0(5);
  if (iVar1 == 0) {
    FUN_000500ac(5);
  }
  *(volatile uint32_t*)0x50005518UL = 1;
  *(volatile uint32_t*)0x50005514UL = 1;
  *(volatile uint32_t*)0x50005580UL = 1;
}

