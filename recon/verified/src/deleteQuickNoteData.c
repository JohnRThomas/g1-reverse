/* Reconstructed deleteQuickNoteData @ 0x244a8  (parity: 300/300 trials, PROVEN) */
extern int FUN_000720d0(unsigned int a0, void *a1, unsigned int a2, unsigned int a3);
extern void DEBUG_PRINT(unsigned int a0, ...);
extern void FUN_00019c70(void);
extern void FUN_00072880(unsigned int a0);

unsigned int deleteQuickNoteData(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int buf[3];
    int iVar1;
    unsigned int uVar2;
    (void)param_2;
    buf[0] = 0x00010002UL;
    buf[1] = (unsigned int)(unsigned char)param_1;
    buf[2] = param_3;
    iVar1 = FUN_000720d0(0x20003960UL, buf, 0UL, 0UL);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0)
                DEBUG_PRINT(0x9ee23UL, 0x9f080UL, param_1);
            else
                FUN_00019c70();
        }
        FUN_00072880(0x200079e4UL);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0)
                DEBUG_PRINT(0x9edc2UL, 0x9f080UL);
            else
                FUN_00019c70();
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

