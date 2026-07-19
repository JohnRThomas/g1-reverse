#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_cbor_decoder_state__param_0715         [param_0715; library]
 * Raw function identity: 0x00085c12.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00085c12 @ 0x00085c12
 * public-name: cbor_decoder_at_end
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decoder_at_end                      <= FUN_00085c12 @ 0x00085c12
 */
/* Reconstructed FUN_00085c12 @ 0x85c12  (parity: 300/300 trials, PROVEN) */

int cbor_decoder_at_end(int param_1)
{
    if (param_1 != 0 && *(char *)(param_1 + 0x10) != 0) {
        return *(int *)(param_1 + 0xc) == 0;
    }
    return 1;
}
