/* Reconstructed FUN_00034944 @ 0x34944  (parity: 300/300 trials, PROVEN) */

extern int FUN_0003441c(void);
extern void FUN_00086c78(int a, int b, int c);
extern void FUN_00035744(void);

void FUN_00034944(void)
{
    *(volatile unsigned char *)0x2001a22bUL = 10;
    *(volatile unsigned char *)0x2001a22aUL = 0;
    *(volatile unsigned char *)0x2001a229UL = 0;
    int uVar1 = FUN_0003441c();
    FUN_00086c78(0x20007dac, uVar1, 0x2210);
    FUN_00035744();
}

