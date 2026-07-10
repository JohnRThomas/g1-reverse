#include "g1_app_symbols.h"
/* named: bt_security_err_lookup */
/* Reconstructed bt_security_err_lookup @ 0x54250  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint8_t bt_security_err_lookup(unsigned int param_1)
{
  uint8_t uVar1;
  if (param_1 < 0x2a) {
    uVar1 = *(volatile uint8_t*)(((uintptr_t)&rodata_f33e9) /*=0xf33e9*/ + param_1);
  } else {
    uVar1 = 9;
  }
  return uVar1;
}

