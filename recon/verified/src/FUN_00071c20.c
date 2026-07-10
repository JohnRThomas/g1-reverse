/* Reconstructed FUN_00071c20 @ 0x71c20  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072040(int);
extern int FUN_0007205c(int);
extern void FUN_00072078(int);
extern int FUN_00073f6c(int,unsigned,int,int,int,int,int);
extern void FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned,...);

int FUN_00071c20(int param_1, int *param_2, int param_3, int param_4){
    int iVar6 = param_1 + 8;
    unsigned uVar7 = 0;
    int iVar3 = FUN_00072040(iVar6);
    if (iVar3 == 0){
        FUN_0007e2fa(0x99cbd, 0x000f0920, 0x000f08c7, 0x72, param_1, param_2);
        FUN_0007e2fa(0x000f0935, iVar6);
        uVar7=0x72;
        FUN_0007e2ec(0x000f08c7, uVar7);
        return 0x72;
    }
    FUN_00072078(iVar6);
    int *puVar4 = *(int**)(param_1+0x18);
    int ret;
    if (puVar4 == 0){
        if (param_3 != 0 || param_4 != 0){
            int r = FUN_00073f6c(iVar6, uVar7, param_1, 0, param_3, param_4, param_3);
            if (r != 0) return r;
            *param_2 = *(int*)(*(int*)(0x2000b448+8)+0x14);
            return 0;
        }
        ret = -0xc;
        *param_2 = 0;
    } else {
        *param_2 = (int)puVar4;
        *(int*)(param_1+0x18) = *puVar4;
        *(int*)(param_1+0x1c) = *(int*)(param_1+0x1c) + 1;
        ret = 0;
    }
    iVar3 = FUN_0007205c(iVar6);
    if (iVar3 != 0){
        return ret;
    }
    FUN_0007e2fa(0x99cbd, 0x000f08f4, 0x000f08c7, 0xf0, param_1, param_2);
    FUN_0007e2fa(0x000f090b, iVar6);
    uVar7=0xf0;
    FUN_0007e2ec(0x000f08c7, uVar7);
    return ret;
}

