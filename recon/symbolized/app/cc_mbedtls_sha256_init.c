#include "g1_app_symbols.h"
/* named: cc_mbedtls_sha256_init */
/* Reconstructed cc_mbedtls_sha256_init @ 0x7abc0  (parity: 300/300 trials, PROVEN) */

extern void CC_PalAbort(unsigned int a0);
extern void FUN_0007a3d4(int a0, unsigned int a1);

void cc_mbedtls_sha256_init(int param_1)
{
  if (param_1 != 0) {
    FUN_0007a3d4(param_1, 0xf4);
    return;
  }
  CC_PalAbort("\nctx is NULL\n" /*=0x988a8*/);
  FUN_0007a3d4(0, 0xf4);
}

