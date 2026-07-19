#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085d5c @ 0x00085d5c
 * public-name: cbor_decode_is_exhausted
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_is_exhausted                 <= FUN_00085d5c @ 0x00085d5c
 */
/* Reconstructed FUN_00085d5c @ 0x85d5c  (parity: 300/300 trials, PROVEN) */

int cbor_decode_is_exhausted(int param_1)
{
    if (param_1 != 0 && *(char *)(param_1 + 0x10) != 0) {
        return *(int *)(param_1 + 0xc) == 0;
    }
    return 1;
}
