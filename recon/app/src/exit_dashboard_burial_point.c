/* Reconstructed exit_dashboard_burial_point @ 0x4aab0  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_000167a8(void);
extern unsigned int FUN_0007dac0(void);
extern long long FUN_0004a960(void);
extern unsigned int FUN_0007db50(void);
extern unsigned int DEBUG_PRINT(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned int FUN_00019c70(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int exit_dashboard_burial_point(void)
{
    unsigned int r0v;
    unsigned int base;
    unsigned int uVar2;
    unsigned long long uVar4;
    unsigned int uVar3;

    base = FUN_000167a8() + 0x1000;
    r0v = base;
    if (*(volatile unsigned char*)(base + 0x92) != 0) {
        uVar2 = FUN_0007dac0();
        r0v = uVar2;
        if (uVar2 < 7) {
            base = FUN_000167a8() + 0x1000;
            *(volatile unsigned char*)(base + 0x92) = 0;
            uVar4 = (unsigned long long)FUN_0004a960();
            r0v = (unsigned int)uVar4;
            uVar3 = (unsigned int)(uVar4 >> 32);
            r0v = FUN_0007db50();
            if (1 < *(volatile int*)0x2000230cUL) {
                if (*(volatile unsigned int*)0x20007554UL == 0) {
                    base = FUN_000167a8() + 0x1000;
                    r0v = DEBUG_PRINT(0xf03c4, 0xf0459, (unsigned int)uVar4, uVar3, *(volatile unsigned int*)(base + 0xd2));
                } else {
                    base = FUN_000167a8() + 0x1000;
                    r0v = FUN_00019c70(0xf03c4, 0xf0459, (unsigned int)uVar4, uVar3, *(volatile unsigned int*)(base + 0xd2));
                }
            }
        }
    }
    return r0v;
}

