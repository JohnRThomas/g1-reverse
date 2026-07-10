#include "g1_app_symbols.h"
/* named: cbor_encode_array_indef_start */
/* Reconstructed cbor_encode_array_indef_start @ 0x86344  (parity: 300/300 trials, PROVEN) */

extern void cbor_encode_put_type_byte(unsigned int, unsigned int, unsigned int);
void cbor_encode_array_indef_start(unsigned int param_1)
{
    cbor_encode_put_type_byte(param_1, 4, 0x1f);
}

