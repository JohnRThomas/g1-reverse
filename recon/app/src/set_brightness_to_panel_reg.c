/* Reconstructed set_brightness_to_panel_reg @ 0x46e3c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void *FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_0007d642(int, int);
extern void FUN_0007d67e(unsigned int);
extern void FUN_0007d696(int);
extern void FUN_0007d772(int);
extern void FUN_0007d63e(int);

void set_brightness_to_panel_reg(unsigned int param_1)
{
    unsigned int uVar1;
    short sVar2;
    int iVar3;
    unsigned int uVar4;
    int iVar5;

    if (2 < *(volatile int*)0x2000230cUL) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x000d7251UL, 0x000d7310UL, param_1);
        } else {
            FUN_00019c70(0x000d7251UL, 0x000d7310UL, param_1);
        }
    }
    FUN_0007d63e(6);
    FUN_0007d63e(0xa9);
    if (5 < param_1) {
        iVar3 = (int)(intptr_t)FUN_000167a8();
        FUN_0007d696((int)((*(short*)(intptr_t)(iVar3 + 0xed8) + 1) * 0x6f));
        uVar4 = (param_1 - 6) & 0xff;
        goto LAB_00046ea0;
    }
    iVar3 = (int)(intptr_t)FUN_000167a8();
    uVar1 = ((unsigned int)*(unsigned short*)(intptr_t)(iVar3 + 0xed8) << 1) / 9;
    iVar3 = (int)uVar1;
    if (iVar3 == 0) {
LAB_00046e7a:
        iVar3 = (int)(intptr_t)FUN_000167a8();
        sVar2 = (short)(((short)((param_1 * 0x6f) / 6) + 1) * (*(short*)(intptr_t)(iVar3 + 0xed8) + 1));
    } else {
        iVar5 = (int)(intptr_t)FUN_000167a8();
        if (*(unsigned short*)(intptr_t)(iVar5 + 0xed8) < 6) goto LAB_00046e7a;
        iVar5 = (int)(intptr_t)FUN_000167a8();
        sVar2 = (short)(((short)((int)(param_1 * ((unsigned int)*(unsigned short*)(intptr_t)(iVar5 + 0xed8) - iVar3)) / 6) + (short)uVar1) * 0x6f);
    }
    FUN_0007d696(sVar2);
    uVar4 = 0;
LAB_00046ea0:
    FUN_0007d67e(uVar4);
    FUN_0007d642(0x31, 4);
    FUN_0007d63e(0xa3);
    FUN_0007d63e(0x97);
    FUN_0007d772(1);
    return;
}
