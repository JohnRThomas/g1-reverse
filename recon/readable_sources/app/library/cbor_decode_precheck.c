#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_zcbor_state_t__param_0716              [param_0716; library]
 * Raw function identity: 0x00085d82.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00085d82 @ 0x00085d82
 * public-name: cbor_decode_precheck
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_is_exhausted                 <= FUN_00085d5c @ 0x00085d5c
 *   zcbor_backup_store_count                 <= FUN_00085d70 @ 0x00085d70
 *   cbor_decode_precheck                     <= FUN_00085d82 @ 0x00085d82
 */
/* Reconstructed FUN_00085d82 @ 0x85d82  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_is_exhausted(unsigned int);
extern void zcbor_backup_store_count(unsigned int*,unsigned int);
int cbor_decode_precheck(unsigned int *param_1)
{
  int iVar1;
  iVar1 = cbor_decode_is_exhausted(param_1[5]);
  if (iVar1 != 0) {
    if (param_1[0] < param_1[3]) {
      return iVar1;
    }
    zcbor_backup_store_count(param_1,8);
  }
  return 0;
}
