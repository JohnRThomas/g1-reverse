#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086354 @ 0x00086354
 * public-name: cbor_encode_break
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_encode_put_type_byte                <= FUN_000861d4 @ 0x000861d4
 *   cbor_encode_break                        <= FUN_00086354 @ 0x00086354
 */
/* Reconstructed FUN_00086354 @ 0x86354  (parity: 300/300 trials, PROVEN) */

extern void cbor_encode_put_type_byte(unsigned int, unsigned int, unsigned int);
void cbor_encode_break(unsigned int param_1)
{
    cbor_encode_put_type_byte(param_1, 7, 0x1f);
}
