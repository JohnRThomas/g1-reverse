/* Reconstructed gui_screen_clear @ 0x431c0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);
extern int FUN_0007d4ec(void);
extern void FUN_0007d6f4(void);

unsigned int gui_screen_clear(void)
{
    unsigned int uVar3;
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            FUN_00019c70();
        }
    }
    int iVar2 = FUN_0007d4ec();
    int field = *(volatile int*)(iVar2 + 0x35c);
    if (field == 0) {
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT();
            } else {
                FUN_00019c70();
            }
        }
        uVar3 = 0xffffffffUL;
    } else {
        FUN_0007d6f4();
        uVar3 = 0;
    }
    return uVar3;
}

