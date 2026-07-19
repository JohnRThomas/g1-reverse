#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086378 @ 0x00086378
 * public-name: cbor_encode_simple
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   zcbor_simple_put                         <= FUN_00086360 @ 0x00086360
 *   cbor_encode_simple                       <= FUN_00086378 @ 0x00086378
 */
/* Reconstructed FUN_00086378 @ 0x86378 */
#include <stdint.h>

extern void zcbor_simple_put(void *, uint8_t);

void cbor_encode_simple(void *destination, uint8_t value)
{
  zcbor_simple_put(destination, (uint8_t)(value + 0x14));
}
