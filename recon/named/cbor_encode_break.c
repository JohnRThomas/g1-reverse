/* named: cbor_encode_break */
/* Reconstructed cbor_encode_break @ 0x86354  (parity: 300/300 trials, PROVEN) */

extern void cbor_encode_put_type_byte(unsigned int, unsigned int, unsigned int);
void cbor_encode_break(unsigned int param_1)
{
    cbor_encode_put_type_byte(param_1, 7, 0x1f);
}

