/* named: k_heap_alloc */
/* Reconstructed k_heap_alloc @ 0x8099e  (parity: 300/300 trials, PROVEN) */

extern void cbor_encode_bstr(unsigned int a, void *b);

void k_heap_alloc(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int local[3];
    local[0] = param_2;
    local[1] = param_3;
    local[2] = param_3;
    cbor_encode_bstr(param_1, local);
}

