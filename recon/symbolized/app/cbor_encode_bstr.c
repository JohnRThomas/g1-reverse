#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008633e @ 0x0008633e
 * public-name: cbor_encode_bstr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_encode_bstr                         <= FUN_0008633e @ 0x0008633e
 */
/* Reconstructed FUN_0008633e @ 0x8633e */
#include <stdint.h>

extern int FUN_00086228(void *, const void *, uint32_t);

int cbor_encode_bstr(void *destination, const void *item)
{
  return FUN_00086228(destination, item, 3);
}
