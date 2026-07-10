#include "g1_app_symbols.h"
/* named: FUN_000850c8 */
/* Reconstructed FUN_000850c8 @ 0x850c8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int FUN_000850c8(unsigned char *param_1) {
  unsigned int result = (unsigned int)(uintptr_t)param_1;
  if (param_1 != 0) {
    result = (unsigned int)(param_1[0xc] == 0x20);
  }
  return result;
}

