#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008630c @ 0x0008630c
 * public-name: cbor_encode_int32
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_encode_signed_bytes                 <= FUN_0008629e @ 0x0008629e
 *   cbor_encode_int32                        <= FUN_0008630c @ 0x0008630c
 */
/* Reconstructed FUN_0008630c @ 0x8630c  (parity: 300/300 trials, PROVEN) */

extern void cbor_encode_signed_bytes(unsigned int a, unsigned int *b, unsigned int c, unsigned int d, unsigned int e);

void cbor_encode_int32(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int local_c = param_2;
    unsigned int uStack_8 = param_3;
    cbor_encode_signed_bytes(param_1, &local_c, 4, param_4, param_1);
}
