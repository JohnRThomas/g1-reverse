#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008500c @ 0x0008500c
 * public-name: cbor_decode_start_default
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   enqueue_string_with_len                  <= FUN_00084fec @ 0x00084fec
 *   cbor_decode_start_default                <= FUN_0008500c @ 0x0008500c
 */
/* Reconstructed FUN_0008500c @ 0x8500c. */
/* Tail wrapper: clear the callee's second and third ABI arguments. */
extern void enqueue_string_with_len(unsigned int, unsigned int, unsigned int);

void cbor_decode_start_default(unsigned int param_1)
{
    enqueue_string_with_len(param_1, 0, 0);
}
