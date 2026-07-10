#include "g1_app_symbols.h"
/* named: FUN_0007abe8 */
/* Reconstructed FUN_0007abe8 @ 0x7abe8  (parity: 300/300 trials, PROVEN) */

extern void mbedtls_zeroize_internal(int a0, int a1);
void FUN_0007abe8(int param_1)
{
  if (param_1 != 0) {
    mbedtls_zeroize_internal(param_1, 0xf4);
  }
}

