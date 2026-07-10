#include "g1_app_symbols.h"
/* named: cbor_encode_simple */
/* Reconstructed cbor_encode_simple @ 0x86378  (parity: 200/200 trials, PROVEN) */

extern void cbor_encode_length_header(int a, int b, void *c, int d, int e, unsigned int f);
void cbor_encode_simple(int param_1, char param_2)
{
  char local;
  unsigned char v = (unsigned char)(param_2 + 0x14);
  cbor_encode_length_header(param_1, 7, &local, 1, param_1, v);
}

