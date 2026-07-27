/* Reconstructed FUN_00066300 @ 0x66300  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(int a, int b);

unsigned int FUN_00066300(void)
{
    unsigned char bVar1;
    unsigned int uVar3;

    if (*(volatile unsigned char *)0x2000b340UL == 0) {
        FUN_0007e2fa(0x99cbd, 0xf6d26, 0xf6ceb, 0x132, 0);
        FUN_0007e2ec(0xf6ceb, 0x132);
    }
    bVar1 = *(volatile unsigned char *)0x2000b341UL;
    if (bVar1 == 1) {
        *(volatile unsigned char *)0x2000b340UL = 1;
        *(volatile unsigned char *)0x2000b341UL = 3;
        *(volatile unsigned int *)0x50026004UL = (unsigned int)bVar1;
        uVar3 = 0x0bad0000;
    } else if (bVar1 == 0 || bVar1 == 2) {
        *(volatile unsigned int *)0x50026500UL = 0;
        *(volatile unsigned char *)0x2000b341UL = 0;
        uVar3 = 0x0bad0000;
    } else {
        uVar3 = 0x0bad000b;
    }
    return uVar3;
}

