#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000861ae @ 0x000861ae
 * public-name: cbor_encode_check_ok
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_encode_check_ok                     <= FUN_000861ae @ 0x000861ae
 */
/* Reconstructed FUN_000861ae @ 0x861ae  (parity: 300/300 trials, PROVEN) */

int cbor_encode_check_ok(int param_1)
{
    if (param_1 != 0 && *(char *)(param_1 + 0x10) != 0) {
        return *(int *)(param_1 + 0xc) == 0;
    }
    return 1;
}
