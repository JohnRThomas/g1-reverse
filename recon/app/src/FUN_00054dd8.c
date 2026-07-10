/* Reconstructed FUN_00054dd8 @ 0x54dd8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned,...);
extern int FUN_00080fa4(int,int);
extern int FUN_00086be4(int,void*,int);
extern void FUN_00086c78(void*,int,int);

void FUN_00054dd8(int param_1, int *param_2){
    unsigned char auStack_30[24];
    unsigned uVar3;
    if (param_2 == 0){
        FUN_0007e2fa(0x99cbd, 0x000f3537, 0x000f3509, 0x36c);
        uVar3=0x36c; FUN_0007e2ec(0x000f3509, uVar3); return;
    }
    int iVar4 = *param_2;
    if (iVar4 == 0){
        FUN_0007e2fa(0x99cbd, 0x000f354f, 0x000f3509, 0x36d);
        uVar3=0x36d; FUN_0007e2ec(0x000f3509, uVar3); return;
    } else if (param_1 == 0){
        FUN_0007e2fa(0x99cbd, 0x000f3572, 0x000f3509, 0x36e);
        uVar3=0x36e; FUN_0007e2ec(0x000f3509, uVar3); return;
    } else {
        if (-1 < (int)((unsigned)*(unsigned char*)(iVar4+8) << 0x1d)){
            if (param_2[1] == 0 && (int)((unsigned)*(unsigned char*)(param_1+8) << 0x1d) < 0){
                int iVar1 = FUN_00080fa4(iVar4+1, param_1+1);
                FUN_00086c78(auStack_30, 0, 0x16);
                int iVar2 = FUN_00086be4(iVar4+0x2a, auStack_30, 0x10);
                if ((iVar2 != 0 && FUN_00086be4(iVar4+0x2a, (void*)(param_1+0x2a), 0x10) == 0) || iVar1 != 0){
                    param_2[1] = param_1;
                }
            }
            return;
        }
        FUN_0007e2fa(0x99cbd, 0x000f358a, 0x000f3509, 0x370);
        uVar3=0x370; FUN_0007e2ec(0x000f3509, uVar3); return;
    }
}

