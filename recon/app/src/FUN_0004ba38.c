/* Reconstructed FUN_0004ba38 @ 0x4ba38  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004b4fc(int,int,unsigned,int,unsigned);
extern int FUN_00072040(int);
extern int FUN_0007205c(int);
extern void FUN_00072078(int);
extern void FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned,...);

unsigned FUN_0004ba38(int param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    int iVar7 = param_1 + 0x14;
    unsigned uVar8 = 0;
    int iVar4 = FUN_00072040(iVar7);
    unsigned uVar5 = 0;
    if (iVar4 == 0){
        FUN_0007e2fa(0x99cbd, 0x000f0920, 0x000f08c7, 0x72);
        FUN_0007e2fa(0x000f0935, iVar7);
        uVar5=0x72; uVar8=0x000f08c7;
        FUN_0007e2ec(uVar8, uVar5);
        return uVar5;
    }
    FUN_00072078(iVar7);
    unsigned uVar6 = *(unsigned short*)(param_1+0x1c) & 7;
    if (uVar6 == 2){
        short sVar1 = *(short*)(param_1+0x1e);
        if (sVar1 == 0){
            FUN_0007e2fa(0x99cbd, 0x000f094b, 0x000f0824, 0x1ef);
            FUN_0007e2ec(0x000f0824, 0x1ef);
        }
        unsigned short nv = (unsigned short)(sVar1 - 1);
        *(short*)(param_1+0x1e) = (short)nv;
        uVar5 = 2;
        if (nv == 0){
            FUN_0004b4fc(param_1, 2, uVar8, 0, param_4);
            return 2;
        }
    } else if (uVar6 == 1){
        uVar5 = 0xfffffffb;
    } else {
        uVar5 = 0xffffff7a;
    }
    iVar4 = FUN_0007205c(iVar7);
    if (iVar4 != 0){
        return uVar5;
    }
    FUN_0007e2fa(0x99cbd, 0x000f08f4, 0x000f08c7, 0xf0);
    FUN_0007e2fa(0x000f090b, iVar7);
    uVar5=0xf0; uVar8=0x000f08c7;
    FUN_0007e2ec(uVar8, uVar5);
    return uVar5;
}

