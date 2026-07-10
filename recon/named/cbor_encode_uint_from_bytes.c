/* named: cbor_encode_uint_from_bytes */
/* Reconstructed cbor_encode_uint_from_bytes @ 0x862ee  (parity: 300/300 trials, PROVEN) */

extern unsigned int cbor_encode_length_header(unsigned int, unsigned int, unsigned int, int);
extern void cbor_encode_set_error(unsigned int, unsigned int);

unsigned int cbor_encode_uint_from_bytes(unsigned int param_1, unsigned int param_2, int param_3)
{
  unsigned int uVar1;

  if (param_3 != 0) {
    uVar1 = cbor_encode_length_header(param_1,0,param_2,param_3);
    return uVar1;
  }
  cbor_encode_set_error(param_1,0xe);
  return 0;
}

