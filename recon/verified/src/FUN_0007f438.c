/* Reconstructed FUN_0007f438 @ 0x7f438  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007f3c2(unsigned long);
extern void FUN_0007f3f0(void *a, unsigned int b);

void FUN_0007f438(unsigned int *param_1)
{
    unsigned int base;
    unsigned int fptr;
    FUN_0007f3c2(param_1);
    FUN_0007f3f0(param_1 + 0x4e, 0xfffffffeUL);
    base = param_1[0x57];
    fptr = *(volatile unsigned int*)(base + 4);
    if (fptr != 0) {
        ((void(*)(unsigned int,unsigned int))fptr)(param_1[0], param_1[1]);
    }
}

