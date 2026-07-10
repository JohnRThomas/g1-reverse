/* Reconstructed FUN_000167f4 @ 0x167f4  (parity: 300/300 trials, PROVEN) */

extern void FUN_00015fdc(void);
extern void FUN_000160b4(void);
extern void FUN_0007c038(unsigned int a);
extern int FUN_00083dc8(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void DEBUG_PRINT(unsigned int a);

unsigned int FUN_000167f4(void)
{
    unsigned int format_string;
    FUN_00015fdc();
    FUN_000160b4();
    FUN_0007c038(2000);
    int base = *(volatile int*)(0x00087d10UL + 4);
    unsigned int arg0 = *(volatile unsigned int*)(base + 0x1c);
    int iVar1 = FUN_00083dc8(arg0, 0xb, 2, 1, 0);
    if (iVar1 < 0) {
        format_string = 0x0009973dUL;
    } else {
        format_string = 0x00099756UL;
    }
    DEBUG_PRINT(format_string);
    return 0;
}

