/* Reconstructed SendDashBoardStartupModeInfoToSlave @ 0x48a3c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void*, int, int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

unsigned int SendDashBoardStartupModeInfoToSlave(int param_1)
{
    int iVar1;
    unsigned int uVar2, uVar3;
    unsigned char buf[24];

    FUN_00086c78(buf + 1, 0, 0x17);
    buf[0] = 6;
    buf[4] = (unsigned char)param_1;
    *(unsigned short*)(buf + 2) = 1;
    iVar1 = FUN_000720d0(0x2000392cUL, buf, 0, 0);
    if (iVar1 == 0) {
        uVar3 = 0;
        if (2 < *(volatile int*)0x2000230cUL) {
            uVar2 = 0xef5f3;
            if (param_1 == 1) {
                uVar2 = 0xef5df;
            }
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xef603, 0xef6b0, uVar2, 0xef5df);
            } else {
                FUN_00019c70(0xef603, 0xef6b0, uVar2, 0xef5df);
            }
        }
    } else {
        DEBUG_PRINT(0xef058, 0xef6b0);
        uVar3 = 0xffffffff;
    }
    return uVar3;
}
