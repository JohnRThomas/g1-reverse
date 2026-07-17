#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085d82 @ 0x00085d82
 * public-name: cbor_decode_precheck
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_precheck                     <= FUN_00085d82 @ 0x00085d82
 */
/* Reconstructed FUN_00085d82 @ 0x85d82  (parity: 300/300 trials, PROVEN) */

extern int FUN_00085d5c(unsigned int);
extern void FUN_00085d70(unsigned int*,unsigned int);
int cbor_decode_precheck(unsigned int *param_1)
{
  int iVar1;
  iVar1 = FUN_00085d5c(param_1[5]);
  if (iVar1 != 0) {
    if (param_1[0] < param_1[3]) {
      return iVar1;
    }
    FUN_00085d70(param_1,8);
  }
  return 0;
}
