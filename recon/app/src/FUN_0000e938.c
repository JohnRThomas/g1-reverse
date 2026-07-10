/* Reconstructed FUN_0000e938 @ 0xe938  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_0000d848(int a);
extern int FUN_0000de2c(int a,int b,int c,int d,int e);
int FUN_0000e938(float param_1) {
    int r0;
    __builtin_memcpy(&r0, &param_1, 4);
    unsigned long long uVar3 = FUN_0000d848(r0);
    int lo = (int)uVar3;
    int hi = (int)(uVar3 >> 32);
    int iVar1 = FUN_0000de2c(lo, hi, lo, hi, 0);
    if (iVar1 != 0) iVar1 = 1;
    return iVar1;
}

