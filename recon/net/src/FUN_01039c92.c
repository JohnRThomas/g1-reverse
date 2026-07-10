/* net-core FUN_01039c92 @ 0x1039c92  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01039c3c(int *a, ...);
extern int FUN_01039c20(int *a, ...);
extern void FUN_01039c54(int *a, int b);

typedef int (*fnptr)(int);

unsigned int FUN_01039c92(int *param_1, int param_2, int *param_3, int *param_4)
{
    int iVar8 = param_1[3];
    int iVar7 = param_1[8];
    int iVar9 = iVar7 + iVar8 * 4;
    unsigned int uVar2;

    if ((*(volatile unsigned char *)(iVar7 + iVar8 * 4) & 3) == 2) {
        unsigned int uVar6 = *(volatile unsigned int *)(iVar7 + iVar8 * 4);
        *param_3 = 0;
        *param_4 = 0;
        if ((uVar6 >> 2) == 0) {
            goto LAB_cbc;
        }
        FUN_01039c3c(param_1);
        param_1[2] = param_1[3];
    LAB_ce0:
        uVar2 = 1;
        return uVar2;
    } else {
        *param_3 = 0;
        *param_4 = 0;
    LAB_cbc:
        if ((param_1[4] << 0x1e) < 0) {
            int iVar3 = ((fnptr)param_1[7])(iVar9);
            unsigned char bVar1 = *(volatile unsigned char *)(iVar7 + iVar8 * 4);
            int iVar5 = (int)((unsigned int)bVar1 << 0x1f);
            if (iVar5 < 0) {
                unsigned int uVar6 = bVar1 & 2;
                if (uVar6 == 0) {
                    FUN_01039c3c(param_1);
                    param_1[2] = param_1[3];
                    if (param_2 != 0) {
                        *(volatile unsigned int *)(param_1[8] + *param_1 * 4) = uVar6;
                    }
                    *param_4 = iVar3 + param_2;
                    {
                        int iVar4 = FUN_01039c20(param_1, *param_1);
                        *param_1 = iVar4;
                    }
                    param_1[4] = param_1[4] | 8;
                    *(volatile unsigned char *)(iVar7 + iVar8 * 4) =
                        *(volatile unsigned char *)(iVar7 + iVar8 * 4) & 0xfe;
                    *param_3 = iVar9;
                } else {
                    if (param_2 != 0) {
                        FUN_01039c54(param_1, param_2);
                    }
                    iVar7 = FUN_01039c20(param_1, param_1[1], iVar3);
                    param_1[1] = iVar7;
                    if (param_1[3] == param_1[2]) {
                        iVar7 = FUN_01039c20(param_1, param_1[3], iVar3);
                        param_1[2] = iVar7;
                    }
                    *param_1 = param_1[2];
                    param_1[3] = param_1[2];
                    param_1[4] = param_1[4] | 8;
                }
                goto LAB_ce0;
            }
        }
        uVar2 = 0;
    }
    return uVar2;
}

