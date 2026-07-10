/* Reconstructed FUN_00060f20 @ 0x60f20  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00060990(int,...);
extern int FUN_000609f4(int,...);
extern int FUN_00060a10(int,...);
extern int FUN_00060a5c(int,...);
extern int FUN_00072880(int,...);
extern int FUN_000838d6(int,...);
extern int FUN_000838fa(int,...);
extern int FUN_00083906(int,...);
extern int FUN_0008392e(int,...);
extern int FUN_00083954(int,...);
extern int FUN_00085200(int,...);
extern int FUN_00085206(int,...);
extern int FUN_00086c04(int,...);

int FUN_00060f20(int param_1, unsigned param_2, unsigned char *param_3, unsigned param_4)
{
    int iVar1, iVar2;
    unsigned uVar3;
    unsigned local_48, local_44, uStack_40, local_3c;
    unsigned char auStack_38[20];

    if (param_3 == 0 || param_4 == 0 || (4 < param_4 && (param_4 & 3) != 0) || (param_2 & 3) != 0)
        return -0x16;
    if ((int)param_2 < 0 || *(unsigned*)(*(int*)(param_1+4)+0x2c) < param_2 + param_4) {
        local_44 = 0x000f5cd8;
        local_48 = 4;
        uStack_40 = param_2;
        local_3c = param_4;
        FUN_000838d6(0x00088270, 0x2040, &local_48);
        return -0x16;
    }
    iVar1 = FUN_00060a10(param_1);
    if (iVar1 != 0) goto LAB_00061054;
    FUN_000838fa(*(unsigned*)(param_1+0x10));
    iVar2 = FUN_00083954(param_1, 0);
    FUN_00083906(param_1);
    iVar1 = 0x0bad0000;
    if (iVar2 == 0) {
        if (param_4 < 4) {
            iVar2 = FUN_00085206((int)auStack_38, 4, param_2);
            FUN_000609f4(*(unsigned*)(param_1+0x10), iVar2);
            if (iVar2 == 0x0bad0000) {
                FUN_00086c04((int)auStack_38, param_3, param_4);
                param_4 = 4;
                param_3 = auStack_38;
LAB_00060fd6:
                iVar2 = FUN_00085200((int)param_3, param_4, param_2);
                FUN_000609f4(*(unsigned*)(param_1+0x10), iVar2);
            }
        } else {
            if (((unsigned)param_3 & 0xe0000000) == 0x20000000 && ((unsigned)param_3 & 3) == 0)
                goto LAB_00060fd6;
            do {
                uVar3 = param_4;
                if (0xf < param_4) uVar3 = 0x10;
                FUN_00086c04((int)auStack_38, param_3, uVar3);
                iVar2 = FUN_00085200((int)auStack_38, uVar3, param_2);
                FUN_000609f4(*(unsigned*)(param_1+0x10), iVar2);
                if (iVar2 != iVar1) break;
                param_4 -= uVar3;
                param_3 += uVar3;
                param_2 += uVar3;
            } while (param_4 != 0);
        }
    }
    FUN_0008392e(param_1);
    iVar1 = FUN_00083954(param_1, 1);
    FUN_00072880(*(unsigned*)(param_1+0x10));
    if (iVar2 == 0) iVar2 = iVar1;
    iVar1 = FUN_00060990(iVar2);
LAB_00061054:
    FUN_00060a5c(param_1);
    return iVar1;
}

