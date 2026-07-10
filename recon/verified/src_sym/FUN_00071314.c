/* Reconstructed FUN_00071314 @ 0x71314  (parity: 300/300 trials, PROVEN) */

extern void FUN_000859b6(int a);
extern void thunk_FUN_00072880(int a);

int FUN_00071314(int param_1)
{
    int iVar1;

    iVar1 = 0xfffff82d;
    if (param_1 != 0) {
        FUN_000859b6(param_1 + 0x58);
        iVar1 = 0xfffff82e;
        if (*(volatile int *)(*(volatile int *)(param_1 + 0xa0) + 0x18) == 0) {
            iVar1 = *(volatile int *)(param_1 + 0x94) + -0x10;
            if (iVar1 < 1) {
                iVar1 = -0x7d2;
            }
        }
        thunk_FUN_00072880(param_1 + 0x58);
    }
    return iVar1;
}

