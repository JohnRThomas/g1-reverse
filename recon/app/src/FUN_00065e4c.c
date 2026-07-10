/* Reconstructed FUN_00065e4c @ 0x65e4c  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_0007e2ec(unsigned int a, unsigned int b);
extern void FUN_0007e2fa(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void FUN_00065e4c(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int r0 = param_1;
    if (*(volatile unsigned char*)0x2000b328UL != 1) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f6c09UL, 0x000f6bc5UL, 0x72, param_4);
        r0 = FUN_0007e2ec(0x000f6bc5UL, 0x72);
    }
    *(volatile int*)0x5002a308UL = 1 << (r0 & 0xff);
}

