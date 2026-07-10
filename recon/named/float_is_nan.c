/* named: float_is_nan */
/* Reconstructed float_is_nan @ 0xe938  (parity: 300/300 trials, PROVEN) */

extern unsigned long long __extendsfdf2(int a);
extern int double_is_unordered(int a,int b,int c,int d,int e);
int float_is_nan(float param_1) {
    int r0;
    __builtin_memcpy(&r0, &param_1, 4);
    unsigned long long uVar3 = __extendsfdf2(r0);
    int lo = (int)uVar3;
    int hi = (int)(uVar3 >> 32);
    int iVar1 = double_is_unordered(lo, hi, lo, hi, 0);
    if (iVar1 != 0) iVar1 = 1;
    return iVar1;
}

