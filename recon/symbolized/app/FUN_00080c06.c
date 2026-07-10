#include "g1_app_symbols.h"
/* named: FUN_00080c06 */
/* Reconstructed FUN_00080c06 @ 0x80c06  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void FUN_00080c06(volatile int *param_1)
{
  if (*param_1 != 0) {
    *param_1 = 0;
    *(volatile uint8_t*)((int*)param_1 + 1) = 0;
  }
  return;
}

