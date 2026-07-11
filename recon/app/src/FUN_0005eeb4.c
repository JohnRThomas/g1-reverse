/* Reconstructed FUN_0005eeb4 @ 0x5eeb4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072040(void);
extern int FUN_0007205c(void);
extern void FUN_00072078(void);
extern int FUN_000727ac(void);
extern void FUN_0007e2ec(void);
extern void FUN_0007e2fa(void);
extern void FUN_00086518(void);
extern void FUN_0008669c(void);
extern void FUN_000866e4(void);

int FUN_0005eeb4(int param_1, unsigned param_2, int param_3, int param_4)
{
    unsigned local_24 = param_2;
    int r4 = 0;
    int iVar6;
    unsigned uVar_h, uVar2, uVar1;

    FUN_0008669c();
    if (param_1 == 0) {
        FUN_0007e2fa();
        FUN_0007e2ec();
        goto CONTINUE_AFTER_FATAL;
    }
    {
        int iVar6b = FUN_00072040();
        if (iVar6b == 0) {
            FUN_0007e2fa();
            FUN_0007e2fa();
            FUN_0007e2ec();
            goto CONTINUE_AFTER_FATAL;
        }
    }
CONTINUE_AFTER_FATAL:
    FUN_00072078();
    uVar_h = *(volatile uint16_t*)(param_1 + 0x22);
    if (uVar_h == 0) {
        int t = FUN_0007205c();
        if (t == 0) goto EF40;
        r4 = FUN_000727ac();
        if (r4 != 0) goto EF60;
        return 0;
    } else {
        uVar2 = *(volatile uint16_t*)(param_1 + 0x20);
        if (uVar2 <= uVar_h) goto EFA0;
        r4 = FUN_000727ac();
        if (r4 == 0) goto EFA0;
        {
            int t = FUN_0007205c();
            if (t == 0) goto EF40;
            goto EF60;
        }
    }
EFA0:
    uVar1 = *(volatile uint16_t*)(param_1 + 0x22);
    *(volatile uint16_t*)(param_1 + 0x22) = (uint16_t)(uVar1 - 1);
    {
        int t = FUN_0007205c();
        if (t == 0) goto EF40;
    }
    {
        unsigned p20 = *(volatile uint16_t*)(param_1 + 0x20);
        unsigned mul = ((unsigned)*(volatile uint8_t*)(param_1 + 0x24) + 0x1b) & 0xfffffffc;
        int d = ((int)(param_1 - 0x20003a7c)) >> 2;
        r4 = (int)((p20 - uVar1) * mul) + *(volatile int*)(param_1 + 0x30);
        *(volatile int8_t*)(r4 + 10) = (int8_t)((uint32_t)0xc4ec4ec5 * (uint32_t)d);
        *(volatile uint8_t*)(r4 + 0xb) = *(volatile uint8_t*)(param_1 + 0x24);
    }
    goto EF60;
EF60:
    {
        unsigned r5v = local_24;
        if (r5v == 0) {
            *(volatile int*)(r4 + 0x14) = 0;
            goto EF2E;
        }
        FUN_000866e4();
        {
            unsigned idx = *(volatile uint8_t*)(r4 + 0xa);
            int p = *(volatile int*)(0x34 * idx + 0x20003a7c + 0x2c);
            int p2 = *(volatile int*)p;
            int fn = *(volatile int*)p2;
            iVar6 = ((int(*)(int,int,int,int))(intptr_t)fn)(r4, (int)(intptr_t)&local_24, param_1, param_2);
            *(volatile int*)(r4 + 0x14) = iVar6;
            if (iVar6 == 0) {
                FUN_00086518();
                return 0;
            }
            if (r5v <= local_24) goto EF2E;
            FUN_0007e2fa();
            FUN_0007e2fa();
            FUN_0007e2ec();
            goto CONTINUE_AFTER_FATAL;
        }
    }
EF2E:
    *(volatile int*)(r4 + 4) = 0;
    *(volatile uint16_t*)(r4 + 8) = 1;
    *(volatile uint16_t*)(r4 + 0x10) = 0;
    *(volatile uint16_t*)(r4 + 0x12) = (uint16_t)local_24;
    *(volatile int*)(r4 + 0xc) = *(volatile int*)(r4 + 0x14);
    return r4;
EF40:
    FUN_0007e2fa();
    FUN_0007e2fa();
    FUN_0007e2ec();
    goto CONTINUE_AFTER_FATAL;
}
