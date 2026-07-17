#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008634c @ 0x0008634c
 * public-name: cbor_encode_map_indef_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_encode_put_type_byte                <= FUN_000861d4 @ 0x000861d4
 *   cbor_encode_map_indef_start              <= FUN_0008634c @ 0x0008634c
 */
/* Reconstructed FUN_0008634c @ 0x8634c  (parity: 300/300 trials, PROVEN) */

extern void cbor_encode_put_type_byte(unsigned int, unsigned int, unsigned int);
void cbor_encode_map_indef_start(unsigned int param_1)
{
    cbor_encode_put_type_byte(param_1, 5, 0x1f);
}
