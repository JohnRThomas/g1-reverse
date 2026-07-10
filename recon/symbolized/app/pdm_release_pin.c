#include "g1_app_symbols.h"
/* named: pdm_release_pin */
/* Reconstructed pdm_release_pin @ 0x66130  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00065ff4(int *p);

void pdm_release_pin(int param_1, unsigned int param_2, unsigned int param_3)
{
  int local_c = param_1;
  unsigned int uStack_8 = param_3;
  (void)uStack_8;
  int iVar1 = FUN_00065ff4(&local_c);
  iVar1 = iVar1 + local_c * 4;
  volatile uint32_t *p = (volatile uint32_t *)(iVar1 + 0x200);
  *p = (0xfffcf0f0u & *p) | 2;
}

