/* Reconstructed FUN_0007f40c @ 0x7f40c  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(unsigned int, unsigned int, unsigned int);
extern void FUN_0007f3c2(unsigned long);
extern void FUN_0007f3f0(unsigned int*, unsigned int);

void FUN_0007f40c(unsigned int *param_1, unsigned int param_2)
{
    FUN_0007f3c2(param_1);
    FUN_0007f3f0(param_1 + 0x4e, 0xfffffffeU);
    fn_t f = *(fn_t*)(param_1[0x57] + 8);
    if (f != (fn_t)0) {
        f(param_1[0], param_2, param_1[1]);
        return;
    }
    return;
}

