/* Reconstructed FUN_0005f338 @ 0x5f338  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void* FUN_0005f304(void*);
extern void FUN_0007e2ec(void);
extern void FUN_0007e2fa(void);

void FUN_0005f338(int *param_1, int *param_2)
{
    if (param_1 == 0) {
        FUN_0007e2fa();
        FUN_0007e2ec();
        return;
    }
    if (param_2 != 0) {
        int *iVar3 = *(volatile int**)((char*)param_1 + 4);
        if (iVar3 != 0) {
            int *iVar1 = (int*)FUN_0005f304(param_2);
            *(volatile int**)((char*)iVar1 + 4) = iVar3;
        }
        *(volatile int**)((char*)param_1 + 4) = param_2;
        return;
    }
    FUN_0007e2fa();
    FUN_0007e2ec();
}
