/* Reconstructed upgradeAppLanguageInfoToFlash @ 0x23af0  (parity: 300/300 trials, PROVEN) */
extern int FUN_000720d0(unsigned int a0, void *a1, unsigned int a2, unsigned int a3);
extern void DEBUG_PRINT(unsigned int a0, ...);
extern void FUN_00019c70(unsigned int,...);
extern void FUN_00072880(unsigned int a0);

unsigned int upgradeAppLanguageInfoToFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int buf[3];
    int iVar1;
    unsigned int uVar2;
    buf[0] = 0x10001UL;
    /* The shipped frame reuses the saved second argument for this word,
       clears its low halfword, then publishes the language byte. */
    buf[1] = (param_2 & 0xffff0000UL) | (unsigned int)(unsigned char)param_1;
    buf[2] = param_3;
    iVar1 = FUN_000720d0(0x20003994UL, buf, 0UL, 0UL);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)0x2000230cUL) {
            unsigned int sink = *(volatile unsigned int*)0x20007554UL;
            if (sink == 0)
                DEBUG_PRINT(0x9e932UL, 0x9eda4UL, param_1, sink);
            else
                FUN_00019c70(0x9e932UL, 0x9eda4UL, param_1, sink);
        }
        FUN_00072880(0x200079e4UL);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            unsigned int sink = *(volatile unsigned int*)0x20007554UL;
            if (sink == 0)
                DEBUG_PRINT(0x9e903UL, 0x9eda4UL, 0UL, sink);
            else
                FUN_00019c70(0x9e903UL, 0x9eda4UL, 0UL, sink);
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}
