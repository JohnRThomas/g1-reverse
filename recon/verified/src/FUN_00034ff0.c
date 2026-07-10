/* Reconstructed FUN_00034ff0 @ 0x34ff0  (parity: 300/300 trials, PROVEN) */

extern void FUN_00019c70(void);
extern void FUN_0007dda4(int a);
extern int FUN_00087036(int a, int b, int c);

unsigned int FUN_00034ff0(int param_1, int param_2)
{
    int iVar1, iVar2, iVar3;

    if (param_1 == 0 || param_2 == 0) {
        if (*(volatile int *)0x20007554UL == 0) {
            FUN_0007dda4(0xa8750);
        } else {
            FUN_00019c70();
        }
    } else {
        iVar3 = 0x2001a22c + (unsigned int)(*(volatile unsigned char *)0x2001a22dUL) * 0x38;
        for (iVar2 = 0x2001a22c; iVar2 != iVar3; iVar2 += 0x38) {
            iVar1 = FUN_00087036(iVar2 + 2, param_1, 0x28);
            if (iVar1 == 0 && (iVar1 = FUN_00087036(iVar2 + 0x2a, param_2, 0x10), iVar1 == 0)) {
                return 1;
            }
        }
    }
    return 0;
}

