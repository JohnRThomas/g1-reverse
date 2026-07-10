/* named: cbor_encode_map_indef_start */
/* Reconstructed cbor_encode_map_indef_start @ 0x8634c  (parity: 300/300 trials, PROVEN) */

extern void cbor_encode_put_type_byte(unsigned int, unsigned int, unsigned int);
void cbor_encode_map_indef_start(unsigned int param_1)
{
    cbor_encode_put_type_byte(param_1, 5, 0x1f);
}

