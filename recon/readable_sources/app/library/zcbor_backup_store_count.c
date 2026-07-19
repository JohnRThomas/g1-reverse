#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_zcbor_state_t__param_0716              [param_0716; library]
 * Raw function identity: 0x00085d70.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00085d70 @ 0x00085d70
 * public-name: zcbor_backup_store_count
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_is_exhausted                 <= FUN_00085d5c @ 0x00085d5c
 *   zcbor_backup_store_count                 <= FUN_00085d70 @ 0x00085d70
 */
/* Reconstructed FUN_00085d70 @ 0x85d70  (parity: 300/300 trials, PROVEN) */

extern unsigned long long cbor_decode_is_exhausted(int a);

void zcbor_backup_store_count(int param_1)
{
    int iVar1 = *(int *)(param_1 + 0x14);
    unsigned long long uVar2 = cbor_decode_is_exhausted(iVar1);
    if ((int)uVar2 != 0 && iVar1 != 0) {
        *(int *)(iVar1 + 0xc) = (int)(uVar2 >> 32);
    }
}
