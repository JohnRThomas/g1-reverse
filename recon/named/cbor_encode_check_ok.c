/* named: cbor_encode_check_ok */
/* Reconstructed cbor_encode_check_ok @ 0x861ae  (parity: 300/300 trials, PROVEN) */

int cbor_encode_check_ok(int param_1)
{
    if (param_1 != 0 && *(char *)(param_1 + 0x10) != 0) {
        return *(int *)(param_1 + 0xc) == 0;
    }
    return 1;
}

