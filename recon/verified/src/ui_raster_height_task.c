/* Reconstructed ui_raster_height_task @ 0x430c0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void *FUN_000167a8(void);
extern void FUN_00019c70(uint32_t, ...);
extern void FUN_0003af78(uint32_t, uint32_t, int);
extern void FUN_00042fb0(int*, int*);
extern void FUN_000431c0(void);
extern void FUN_00072880(int);

unsigned int ui_raster_height_task(unsigned int param_1, unsigned int param_2, int param_3)
{
    volatile int *piVar2 = (volatile int*)0x20002540UL;
    volatile int *piVar1 = (volatile int*)0x2000253cUL;
    int iVar3;
    int iVar4;
    int iVar5;
    int local_20 = -1;
    int local_1c = -1;

    if (param_3 == 2) {
        if (2 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x000aa7f2UL, 0x000aa83fUL);
            } else {
                FUN_00019c70(0x000aa7f2UL, 0x000aa83fUL);
            }
        }
        FUN_0003af78(param_1, param_2, 2);
        *piVar2 = -1;
        *piVar1 = -1;
    } else {
        FUN_00042fb0(&local_20, &local_1c);
        iVar5 = local_20;
        if ((local_20 != *piVar2) || (local_1c != *piVar1)) {
            if (2 < *(volatile int*)0x2000230cUL) {
                if (*(volatile int*)0x20007554UL == 0) {
                    DEBUG_PRINT(0x000aa817UL, 0x000aa83fUL);
                } else {
                    FUN_00019c70(0x000aa817UL, 0x000aa83fUL);
                }
            }
            FUN_000431c0();
            iVar3 = local_1c;
            *piVar2 = iVar5;
            *piVar1 = local_1c;
            iVar4 = (int)(intptr_t)FUN_000167a8();
            *(int*)(intptr_t)(iVar4 + 0xec4) = iVar5;
            iVar5 = (int)(intptr_t)FUN_000167a8();
            *(int*)(intptr_t)(iVar5 + 0xeb8) = iVar3;
            FUN_0003af78(param_1, param_2, 1);
            iVar5 = (int)(intptr_t)FUN_000167a8();
            *(unsigned int*)(intptr_t)(iVar5 + 0x104c) = 0x26;
            iVar5 = (int)(intptr_t)FUN_000167a8();
            FUN_00072880(iVar5 + 0x80);
        }
    }
    return 0;
}

