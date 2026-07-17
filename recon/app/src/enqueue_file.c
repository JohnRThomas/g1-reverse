/* Reconstructed enqueue_file @ 0x23514  (parity: 300/300 trials, PROVEN) */

extern void FUN_00072240(unsigned int, void*, int, int);
extern void FUN_00086c1e(void*, unsigned int, unsigned int, int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void FUN_00019c70(unsigned int, ...);

int enqueue_file(unsigned int param_1, unsigned int param_2)
{
    int iVar1;
    unsigned char buf[201];

    if (*(volatile int*)(0x200079a0UL + 0x24) == 0x1e) {
        FUN_00072240(0x200079a0UL, buf, 0, 0);
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x9e824, 0x9e8f6);
            } else {
                FUN_00019c70(0x9e824, 0x9e8f6);
            }
        }
    }
    FUN_00086c1e(buf, param_1, param_2, 0xc9);
    buf[200] = (unsigned char)param_2;
    iVar1 = FUN_000720d0(0x200079a0UL, buf, 0, 0);
    if ((iVar1 != 0) && (0 < *(volatile int*)0x2000230cUL)) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x9e840, 0x9e8f6);
        } else {
            FUN_00019c70(0x9e840, 0x9e8f6);
        }
    }
    return iVar1;
}
