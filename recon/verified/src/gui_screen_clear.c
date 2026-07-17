/* Reconstructed gui_screen_clear @ 0x431c0  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007dda4(unsigned int message, unsigned int function);
extern void FUN_00019c70(void);
extern int FUN_0007d4ec(void);
extern void FUN_0007d6f4(int clear_value);

unsigned int gui_screen_clear(void)
{
    unsigned int uVar3;
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            FUN_0007dda4(0xaa86c, 0xaae0f);
        } else {
            FUN_00019c70();
        }
    }
    int iVar2 = FUN_0007d4ec();
    int field = *(volatile int*)(iVar2 + 0x35c);
    if (field == 0) {
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                FUN_0007dda4(0xaa891, 0xaae0f);
            } else {
                FUN_00019c70();
            }
        }
        uVar3 = 0xffffffffUL;
    } else {
        FUN_0007d6f4(0);
        uVar3 = 0;
    }
    return uVar3;
}
