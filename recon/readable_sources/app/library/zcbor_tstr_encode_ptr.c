#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008099e @ 0x0008099e
 * public-name: zcbor_tstr_encode_ptr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   zcbor_tstr_encode_ptr                    <= FUN_0008099e @ 0x0008099e
 *   cbor_encode_bstr                         <= FUN_0008633e @ 0x0008633e
 */
/* Reconstructed FUN_0008099e @ 0x8099e  (parity: 300/300 trials, PROVEN) */

extern void cbor_encode_bstr(unsigned int a, void *b);

struct work_item {
    unsigned int value;
    unsigned int context;
};

void zcbor_tstr_encode_ptr(unsigned int queue, unsigned int value,
                  unsigned int context)
{
    struct work_item item = { value, context };
    cbor_encode_bstr(queue, &item);
}
