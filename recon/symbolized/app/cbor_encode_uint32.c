#include "g1_app_symbols.h"
/* named: cbor_encode_uint32 */
/* Reconstructed cbor_encode_uint32 @ 0x86320  (parity: 300/300 trials, PROVEN) */

extern void cbor_encode_uint_from_bytes(unsigned int a, unsigned int *b, unsigned int c, unsigned int d, unsigned int e);

void cbor_encode_uint32(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int local_c = param_2;
    unsigned int uStack_8 = param_3;
    cbor_encode_uint_from_bytes(param_1, &local_c, 4, param_4, param_1);
}

