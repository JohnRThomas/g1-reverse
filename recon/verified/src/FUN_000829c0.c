/* Reconstructed FUN_000829c0 @ 0x829c0  (parity: 300/300 trials, PROVEN) */

extern int FUN_00059c04(unsigned long);
extern void FUN_00082932(unsigned int a, unsigned int b, unsigned short c, void *d, int e);

void FUN_000829c0(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4, unsigned short param_5)
{
    unsigned char local_14[8];
    local_14[0] = 0;
    int iVar1 = FUN_00059c04(param_1);
    if (iVar1 != 0) {
        local_14[0] = *(volatile unsigned char*)((char*)iVar1 + 8);
    }
    FUN_00082932(param_3, param_4, param_5, local_14, 1);
}

