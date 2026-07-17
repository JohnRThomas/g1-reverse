/* Reconstructed enqueue_ancs @ 0x18bb4  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void*, int, int);
extern void FUN_00072240(unsigned int, void*, int, int);
extern void FUN_00086c04(void*, unsigned int, int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, ...);
extern void FUN_00019c70(unsigned int, ...);

int enqueue_ancs(unsigned int param_1)
{
    int iVar1;
    unsigned char buf[436];

    FUN_00086c78(buf, 0, 0x1b4);
    if (*(volatile int*)(0x20006a6cUL + 0x10) == 0) {
        iVar1 = 1;
    } else {
        if (*(volatile int*)(0x20006a6cUL + 0x24) == 10) {
            FUN_00072240(0x20006a6cUL, buf, 0, 0);
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x9a964);
            } else {
                FUN_00019c70(0x9a964);
            }
        }
        FUN_00086c04(buf, param_1, 0x1b4);
        iVar1 = FUN_000720d0(0x20006a6cUL, buf, 0, 0);
        if ((iVar1 != 0) && (0 < *(volatile int*)0x2000230cUL)) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x9a981, 0x9b19d);
            } else {
                FUN_00019c70(0x9a981, 0x9b19d);
            }
        }
    }
    return iVar1;
}
