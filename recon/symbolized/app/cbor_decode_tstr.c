#include "g1_app_symbols.h"
/* named: cbor_decode_tstr */
/* Reconstructed cbor_decode_tstr @ 0x85f9c  (parity: 300/300 trials, PROVEN) */

extern void cbor_decode_length_prefix(int*,int,unsigned int,unsigned int,unsigned int);
void cbor_decode_tstr(int *param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  cbor_decode_length_prefix(param_1, param_2, 3, param_4, param_4);
}

