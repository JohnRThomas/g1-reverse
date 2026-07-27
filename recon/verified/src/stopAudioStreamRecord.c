/* Reconstructed stopAudioStreamRecord @ 0x2f80c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void *destination, int value, unsigned int length);
extern int FUN_000720d0(unsigned int queue, void *record,
                        unsigned int wait, unsigned int flags);
extern void FUN_00072880(void *work);
extern void FUN_0007dda4(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

unsigned int stopAudioStreamRecord(void)
{
    unsigned char record[208];
    FUN_00086c78(record + 5, 0, 203);
    record[4] = 3;
    int iVar1 = FUN_000720d0(0x20003890UL, record + 4, 0, 0);
    unsigned int uVar2;
    if (iVar1 == 0) {
        FUN_00072880((void *)0x200079e4UL);
        uVar2 = 0;
    } else {
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                FUN_0007dda4(0xa3f45U, 0xa4959U);
            } else {
                FUN_00019c70(0xa3f45U, 0xa4959U);
            }
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}
