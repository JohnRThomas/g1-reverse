#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007abc0 @ 0x0007abc0
 * public-name: cc_mbedtls_sha256_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   CC_PalAbort                              <= FUN_000795b4 @ 0x000795b4
 *   cc_mbedtls_sha256_init                   <= FUN_0007abc0 @ 0x0007abc0
 * address symbols (name @ address):
 *   rodata_988a8                             @ 0x000988a8
 */
/* Reconstructed FUN_0007abc0 @ 0x7abc0  (parity: 300/300 trials, PROVEN) */

extern void CC_PalAbort(unsigned int a0);
extern void FUN_0007a3d4(int a0, unsigned int a1);

void cc_mbedtls_sha256_init(int param_1)
{
  if (param_1 != 0) {
    FUN_0007a3d4(param_1, 0xf4);
    return;
  }
  CC_PalAbort(((unsigned long)&rodata_988a8) /*=0x988a8*/);
  FUN_0007a3d4(0, 0xf4);
}
