/* Reconstructed FUN_000182c8 @ 0x182c8  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004ed8c(unsigned int a, void *b, unsigned int c, unsigned int d, unsigned int e);
extern void DEBUG_PRINT(unsigned long, ...);

void FUN_000182c8(unsigned int param_1, unsigned short param_2, unsigned int param_3)
{
    int iVar1;
    unsigned int request;
    (void)param_3;
    request = 0x18010000U | (param_2 & 0xff00U);
    iVar1 = FUN_0004ed8c(param_1, &request, 0x00088a00UL, 0x20006abcUL, param_1);
    if (iVar1 != 0) {
        DEBUG_PRINT(0x0009a401UL, iVar1);
    }
}
