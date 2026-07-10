/* Reconstructed FUN_00074274 @ 0x74274  (parity: 300/300 trials, PROVEN) */

extern void FUN_00073cdc(int, int);
extern void FUN_0007e2fa(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned long long FUN_0007e2ec(unsigned int, unsigned int);

void FUN_00074274(int param_1)
{
    int v8 = *(volatile int*)(param_1 + 8);
    int r0;
    if (v8 == 0) {
        FUN_0007e2fa(0x99cbdUL, 0xf85bbUL, 0xf82f4UL, 0x2d2UL);
        unsigned long long rv = FUN_0007e2ec(0xf82f4UL, 0x2d2UL);
        r0 = (int)rv;
    } else {
        r0 = v8;
    }
    FUN_00073cdc(r0, param_1);
    unsigned char b = *(volatile unsigned char*)(param_1 + 0xd);
    *(volatile unsigned char*)(param_1 + 0xd) = b & 0xfd;
    *(volatile int*)(param_1 + 8) = 0;
}

