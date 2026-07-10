/* Reconstructed FUN_00052bf8 @ 0x52bf8  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2fa(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern unsigned int FUN_0007e2ec(unsigned int a, unsigned int b);

void FUN_00052bf8(unsigned int param_1, unsigned int param_2)
{
    volatile unsigned int *pp = (volatile unsigned int*)(0x00087b90UL + 8);
    unsigned int A = *pp;
    unsigned int r4 = *(volatile unsigned int*)A;
    unsigned int arg1, arg2;
    if (r4 == 0) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f2a79UL, 0x000f2a45UL, 0x4d);
        FUN_0007e2fa(0x000f2a99UL, 0, 0, 0);
        FUN_0007e2ec(0x000f2a45UL, 0x4d);
        arg1 = 0x4d;
        arg2 = 0x000f2a45UL;
    } else {
        arg1 = param_1;
        arg2 = param_2;
    }
    {
        void (*fp)(unsigned int, unsigned int, unsigned int) = (void (*)(unsigned int,unsigned int,unsigned int))r4;
        fp(0x00087b90UL, arg1, arg2);
    }
}

