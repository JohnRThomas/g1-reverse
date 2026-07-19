#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_zcbor_state_t__param_0174              [param_0174; library]
 * Raw function identity: 0x000861c2.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000861c2 @ 0x000861c2
 * public-name: cbor_encode_set_error
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_encode_check_ok                     <= FUN_000861ae @ 0x000861ae
 *   cbor_encode_set_error                    <= FUN_000861c2 @ 0x000861c2
 */
/* Reconstructed FUN_000861c2 @ 0x861c2  (parity: 300/300 trials, PROVEN) */

extern unsigned long long cbor_encode_check_ok(int a);

void cbor_encode_set_error(int param_1)
{
    int iVar1 = *(int *)(param_1 + 0x14);
    unsigned long long uVar2 = cbor_encode_check_ok(iVar1);
    if ((int)uVar2 != 0 && iVar1 != 0) {
        *(int *)(iVar1 + 0xc) = (int)(uVar2 >> 32);
    }
}
