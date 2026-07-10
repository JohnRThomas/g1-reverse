/* named: alloc_zeroed_node */
/* Reconstructed alloc_zeroed_node @ 0x84fd4  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(int a, int b, int c);
typedef int (*fnptr)(int);
int alloc_zeroed_node(fnptr param_1) {
    int iVar1 = param_1(0x28);
    if (iVar1 != 0) {
        memset_bytes(iVar1, 0, 0x28);
    }
    return iVar1;
}

