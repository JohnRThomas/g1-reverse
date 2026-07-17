#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085f9c @ 0x00085f9c
 * public-name: cbor_decode_tstr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_tstr                         <= FUN_00085f9c @ 0x00085f9c
 */
/* Reconstructed FUN_00085f9c @ 0x85f9c (exact 6-byte tail wrapper). */
#include <stdint.h>

/* Catalogless internal entry at 0x85ef0; the verifier maps the encoded name
 * directly to that reviewed firmware address. */
extern void FUN_00085ef0(void *object, void *item, uint32_t mode,
                         uint32_t inherited_r3);

void cbor_decode_tstr(void *object, void *item, uint32_t ignored,
                  uint32_t inherited_r3)
{
    (void)ignored;
    FUN_00085ef0(object, item, 3, inherited_r3);
}
