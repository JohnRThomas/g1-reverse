/* Reconstructed FUN_00056654 @ 0x56654  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(int,int,int,int);

int FUN_00056654(int param_1)
{
    volatile int *piVar1;
    int iVar2;
    if (param_1 == 0) {
        FUN_0007e2fa(0x00099cbd, 0x000f3ebd, 0x000f3a5d, 0x509);
        FUN_0007e2ec(0x000f3a5d, 0x509);
        return 0x509;
    }
    piVar1 = (volatile int*)(param_1 + 0xd0);
    iVar2 = *piVar1;
    if (iVar2 == 0) return 0;
    *piVar1 = iVar2 + 1;
    return param_1;
}
