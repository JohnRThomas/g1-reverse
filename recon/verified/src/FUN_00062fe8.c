/* Reconstructed FUN_00062fe8 @ 0x62fe8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0007e2ec(int,int);
extern int FUN_0007e2fa(int, ...);
extern int FUN_0008484e(int,int);
extern int FUN_00084880(int,int);
extern int FUN_000848b0(int);
extern int FUN_00086c04(int,int,int);

int FUN_00062fe8(int param_1, int param_2, unsigned int param_3, int param_4)
{
    int iVar3, iVar4;
    unsigned int uVar5;
    unsigned int *puVar6;
    unsigned int *puVar7;

    puVar7 = *(unsigned int **)(param_1 + 4);
    iVar4 = *(int *)(param_1 + 0x10);
    puVar6 = (unsigned int *)*puVar7;
    if (*(char *)((char *)puVar7 + 8) != '\0') {
        FUN_0007e2fa(0, 0, 0, 0x342);
        FUN_0007e2fa(0);
        FUN_0007e2ec(0, 0x342);
    }
    iVar3 = *(int *)(iVar4 + 0xc);
    if ((*(char *)(iVar3 + 0xca) == '\0') && (*(char *)(iVar3 + 0xcb) == '\0')) {
        *(int *)(iVar3 + 0x74) = param_4;
        if (param_4 < 0x1d1) {
            param_4 = 0x5c;
        } else {
            param_4 = param_4 / 5;
        }
        *(int *)(*(int *)(iVar4 + 0xc) + 0x78) = param_4;
        *(int *)(*(int *)(iVar4 + 0xc) + 0x58) = param_2;
        *(unsigned int *)(*(int *)(iVar4 + 0xc) + 0x5c) = param_3;
        *(int *)(*(int *)(iVar4 + 0xc) + 0x60) = 0;
        *(int *)(*(int *)(iVar4 + 0xc) + 100) = 0;
        *(int *)(*(int *)(iVar4 + 0xc) + 0x68) = 0;
        if ((int)(puVar7[1] << 0x1b) < 0) {
            uVar5 = (unsigned int)*(unsigned char *)(*(int *)(iVar4 + 0xc) + 0xc9);
            if (uVar5 != 0) {
                if (param_3 <= uVar5) {
                    uVar5 = param_3;
                }
                FUN_00086c04(param_2, *(int *)(iVar4 + 0xc) + 0xc4, uVar5);
                param_3 = param_3 - uVar5;
                param_2 = param_2 + uVar5;
                if (param_3 == 0) {
                    *(char *)(*(int *)(iVar4 + 0xc) + 0xc9) =
                         *(char *)(*(int *)(iVar4 + 0xc) + 0xc9) - (char)uVar5;
                    FUN_0008484e(param_1, uVar5);
                    FUN_00084880(param_1, *(int *)(iVar4 + 0xc) + 0x58);
                    FUN_000848b0(param_1);
                    return 0;
                }
            }
        }
        puVar6[0x14d] = param_2;
        puVar6[0x14e] = param_3;
        puVar6[0x44] = 0;
        puVar6[0x53] = 0;
        *(unsigned char *)(*(int *)(iVar4 + 0xc) + 0xca) = 1;
        if ((int)(puVar7[1] << 0x1b) < 0) {
            iVar4 = *(int *)(*(int *)(param_1 + 0x10) + 0xc);
            if (iVar4 != 0) {
                *(unsigned int *)(iVar4 + 0xc0) = *(unsigned int *)(iVar4 + 0xc0) | 2;
            }
            *(int *)(**(int **)(param_1 + 4) + 0x500) = 8;
        }
        *puVar6 = 1;
        return 0;
    }
    return 0xfffffff0;
}

