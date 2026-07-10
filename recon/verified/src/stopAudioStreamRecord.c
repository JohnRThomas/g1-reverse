/* Reconstructed stopAudioStreamRecord @ 0x2f80c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void);
extern int FUN_000720d0(void);
extern void FUN_00072880(void);
extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);

unsigned int stopAudioStreamRecord(void)
{
    FUN_00086c78();
    int iVar1 = FUN_000720d0();
    unsigned int uVar2;
    if (iVar1 == 0) {
        FUN_00072880();
        uVar2 = 0;
    } else {
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT();
            } else {
                FUN_00019c70();
            }
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

