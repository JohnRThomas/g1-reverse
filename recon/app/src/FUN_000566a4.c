/* Reconstructed FUN_000566a4 @ 0x566a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0007e2fa(int, ...);
extern int FUN_0007e2ec(int,int);
extern int FUN_00055aac(int);

void FUN_000566a4(int param_1)
{
    int *piVar4 = (int *)(param_1 + 0xd0);
    int iVar3 = *piVar4;
    *piVar4 = iVar3 - 1;
    if (iVar3 < 1) {
        FUN_0007e2fa(0, 0, 0, 0x525);
        FUN_0007e2fa(0);
        FUN_0007e2ec(0, 0x525);
    }
    if ((*(short *)(param_1 + 2) == 0x101) && (*piVar4 == 0)) {
        FUN_00055aac(param_1);
    }
    return;
}

