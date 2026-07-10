/* named: cbor_encode_set_error */
/* Reconstructed cbor_encode_set_error @ 0x861c2  (parity: 300/300 trials, PROVEN) */

extern unsigned long long cbor_encode_check_ok(int a);

void cbor_encode_set_error(int param_1)
{
    int iVar1 = *(int *)(param_1 + 0x14);
    unsigned long long uVar2 = cbor_encode_check_ok(iVar1);
    if ((int)uVar2 != 0 && iVar1 != 0) {
        *(int *)(iVar1 + 0xc) = (int)(uVar2 >> 32);
    }
}

