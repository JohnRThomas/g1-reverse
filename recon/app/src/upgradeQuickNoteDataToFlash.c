/* Reconstructed upgradeQuickNoteDataToFlash @ 0x24420  (parity: 300/300 trials, PROVEN) */

extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void FUN_00019c70(unsigned int, ...);
extern void FUN_00072880(unsigned int);

int upgradeQuickNoteDataToFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int request[3];
    int iVar1;
    int uVar2;

    request[0] = 0x10001;
    request[1] = (param_2 & 0xffff0000U) | (param_1 & 0xffU);
    request[2] = param_3;
    iVar1 = FUN_000720d0(0x20003960UL, request, 0, 0);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x9edf3, 0x9f094, param_1);
            } else {
                FUN_00019c70(0x9edf3, 0x9f094, param_1);
            }
        }
        FUN_00072880(0x200079e4UL);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x9edc2, 0x9f094);
            } else {
                FUN_00019c70(0x9edc2, 0x9f094);
            }
        }
        uVar2 = -1;
    }
    return uVar2;
}
