#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_zcbor_state_t__param_0174              [param_0174; library]
 * Raw function identity: 0x0008633e.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0008633e @ 0x0008633e
 * public-name: cbor_encode_bstr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   zcbor_str_encode                         <= FUN_00086228 @ 0x00086228
 *   cbor_encode_bstr                         <= FUN_0008633e @ 0x0008633e
 */
/* Reconstructed FUN_0008633e @ 0x8633e */
#include <stdint.h>

extern int zcbor_str_encode(void *, const void *, uint32_t);

int cbor_encode_bstr(void *destination, const void *item)
{
  return zcbor_str_encode(destination, item, 3);
}
