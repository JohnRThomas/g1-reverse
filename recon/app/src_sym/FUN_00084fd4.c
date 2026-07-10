/* Reconstructed FUN_00084fd4 @ 0x84fd4  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(int a, int b, int c);
typedef int (*fnptr)(int);
int FUN_00084fd4(fnptr param_1) {
    /* param_1 is an allocator callback: alloc(0x28); zero-init 0x28 bytes on success. */
    int iVar1 = param_1(0x28);
    if (iVar1 != 0) {
        memset_bytes(iVar1, 0, 0x28);
    }
    return iVar1;
}

