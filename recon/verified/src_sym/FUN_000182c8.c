/* Reconstructed FUN_000182c8 @ 0x182c8  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004ed8c(unsigned int a, void *b, unsigned int c, unsigned int d, unsigned int e);
extern void DEBUG_PRINT(unsigned int a, int b);

void FUN_000182c8(unsigned int param_1, unsigned short param_2, unsigned int param_3)
{
    int iVar1;
    unsigned short local_c;
    unsigned short local_a;
    unsigned int uStack_8;
    local_c = (unsigned short)(param_2 & 0xff00);
    local_a = 0x1801;
    uStack_8 = param_3;
    (void)local_a; (void)uStack_8;
    iVar1 = FUN_0004ed8c(param_1, &local_c, 0x00088a00UL, 0x20006abcUL, param_1);
    if (iVar1 != 0) {
        DEBUG_PRINT(0x0009a401UL, iVar1);
    }
}

