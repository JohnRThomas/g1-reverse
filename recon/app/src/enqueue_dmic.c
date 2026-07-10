/* Reconstructed enqueue_dmic @ 0x2ec5c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c04(void*, unsigned int, int);
extern void FUN_00072240(unsigned int, void*, int, int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void FUN_00019c70(void);

int enqueue_dmic(unsigned int param_1)
{
    int iVar1;
    unsigned char buf[204];

    FUN_00086c04(buf, 0x885cc, 200);
    if (*(volatile int*)(0x20007b7cUL + 0x24) == 8) {
        FUN_00072240(0x20007b7cUL, buf, 0, 0);
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xa3f17, 0xa41e2, 8);
            } else {
                FUN_00019c70();
            }
        }
    }
    FUN_00086c04(buf, param_1, 200);
    iVar1 = FUN_000720d0(0x20007b7cUL, buf, 0, 0);
    if ((iVar1 != 0) && (0 < *(volatile int*)0x2000230cUL)) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT(0xa3f45, 0xa41e2);
        } else {
            FUN_00019c70();
        }
    }
    return iVar1;
}

