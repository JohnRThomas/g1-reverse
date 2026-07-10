/* Reconstructed SlaveDoubleClickEventInject @ 0x48ad4  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void);
extern int FUN_000720d0(void);
extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);

unsigned int SlaveDoubleClickEventInject(void)
{
    FUN_00086c78();
    int iVar1 = FUN_000720d0();
    unsigned int uVar2;
    if (iVar1 == 0) {
        uVar2 = 0;
        if (*(volatile int*)0x2000230cUL > 2) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT();
            } else {
                FUN_00019c70();
            }
        }
    } else {
        DEBUG_PRINT();
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

