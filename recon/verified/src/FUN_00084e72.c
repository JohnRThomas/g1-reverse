/* Reconstructed FUN_00084e72 @ 0x84e72  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004e048(unsigned int a, void *b, unsigned int c, unsigned int d, unsigned int e);
extern unsigned int FUN_0006403c(unsigned int a, unsigned int b);
extern void FUN_0007ef7e(unsigned int a);

unsigned int FUN_00084e72(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    unsigned int uVar2;
    unsigned int local_c;
    local_c = param_2;
    iVar1 = FUN_0004e048(param_1 & 0xff, &local_c, param_3, param_4, param_1);
    if (iVar1 == 0) {
        uVar2 = FUN_0006403c(local_c, param_2);
        FUN_0007ef7e(local_c);
    } else {
        uVar2 = 1;
    }
    return uVar2;
}

