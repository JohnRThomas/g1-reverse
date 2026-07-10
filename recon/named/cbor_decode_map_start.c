/* named: cbor_decode_map_start */
/* Reconstructed cbor_decode_map_start @ 0x85fa2  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_container_start(int, int);
extern void cbor_decode_undo_and_fail(int, int);

int cbor_decode_map_start(int param_1)
{
    int iVar1;
    iVar1 = cbor_decode_container_start(param_1, 5);
    if (iVar1 != 0) {
        if (*(char*)(param_1 + 0x10) != 0) {
            return iVar1;
        }
        if (*(unsigned int*)(param_1 + 8) < 0x7fffffffU) {
            *(unsigned int*)(param_1 + 8) = *(unsigned int*)(param_1 + 8) << 1;
            return iVar1;
        }
        cbor_decode_undo_and_fail(param_1, 5);
    }
    return 0;
}

