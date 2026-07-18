#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086360 @ 0x00086360
 * public-name: zcbor_simple_put
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_encode_length_header                <= FUN_00086208 @ 0x00086208
 */
/* Reconstructed zcbor_simple_put @ 0x00086360.
 * Raw/address back-map: FUN_00086360 / 0x00086360.
 */
#include <stdint.h>

#define zcbor_encode_length_header cbor_encode_length_header
extern int zcbor_encode_length_header(void *state, uint32_t major_type,
                                      const void *value, uint32_t value_size);

int zcbor_simple_put(void *state, uint8_t input)
{
    return zcbor_encode_length_header(state, 7u, &input, 1u);
}
