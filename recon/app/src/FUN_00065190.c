/* Reconstructed FUN_00065190 @ 0x65190  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_0007e2fa(unsigned int a,unsigned int b,unsigned int c,unsigned int d);
extern unsigned int FUN_0007e2ec(unsigned int a,unsigned int b);

unsigned int FUN_00065190(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile int *piVar1 = (volatile int*)0x2000b31cUL;
    unsigned int uVar2;
    int inVal;
    if (param_1 == 0) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f6abfUL, 0x000f6a4eUL, 0x115);
        inVal = (int)FUN_0007e2ec(0x000f6a4eUL, 0x115);
    } else {
        inVal = param_1;
    }
    if (*(volatile unsigned char*)((char*)piVar1+4) == 0) {
        *piVar1 = inVal;
        uVar2 = 0x0bad0000UL;
        *(volatile unsigned char*)((char*)piVar1+4) = 1;
    } else {
        uVar2 = 0x0bad000cUL;
    }
    return uVar2;
}

