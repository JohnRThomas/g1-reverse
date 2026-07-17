#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086378 @ 0x00086378
 * public-name: cbor_encode_simple
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_encode_simple                       <= FUN_00086378 @ 0x00086378
 */
/* Reconstructed FUN_00086378 @ 0x86378 */
#include <stdint.h>

extern void FUN_00086360(void *, uint8_t);

void cbor_encode_simple(void *destination, uint8_t value)
{
  FUN_00086360(destination, (uint8_t)(value + 0x14));
}
