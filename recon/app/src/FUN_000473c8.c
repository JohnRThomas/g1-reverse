/* Reconstructed FUN_000473c8 @ 0x473c8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned long long u64;
extern void DEBUG_PRINT(int,...);
extern void FUN_00019c70(int,...);
extern int FUN_000723b8(int,...);
extern int FUN_00072558(int,...);
extern int FUN_0007d4ec(int,...);
extern int FUN_0007d772(int,...);
extern int FUN_0007d77c(int,...);

unsigned FUN_000473c8(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7)
{
    unsigned char uVar1; int iVar2; unsigned uVar3; int iVar4; unsigned uVar5,uVar6;
    int iVar7,iVar8,iVar9,iVar10;
    unsigned char local_38[4]; unsigned local_34; unsigned local_30; unsigned char local_2c;

    local_38[0] = 0;
    iVar2 = FUN_0007d4ec(0);
    if(*(int*)(iVar2+0x35c) == 0){
        if(0 < *(volatile int*)0x2000230c){
            if(*(volatile int*)0x20007554 == 0){ DEBUG_PRINT(0x000aa891,0x000d7426); }
            else { FUN_00019c70(0x000aa891, 0x000d7426); }
        }
        uVar3 = 0xffffffff;
    } else {
        uVar3 = 0x140;
        if(199 < param_6) param_6 = 200;
        if(0x27f < param_5) param_5 = 0x280;
        iVar9 = (5 - param_3/2) + param_5/2;
        uVar5 = (param_3 + param_1) & 0x3ff;
        for(; param_4 <= param_6; param_4 = param_4 + 1){
            iVar10 = *(int*)(iVar2+0x344);
            iVar8 = param_4*0x140 + param_7*0x140 + param_3/2 - 5;
            iVar7 = iVar10 + iVar8;
            volatile unsigned char *pixel = (volatile unsigned char *)iVar7;
            local_2c = *(unsigned char*)(iVar7+4);
            local_30 = *(unsigned*)(iVar10+iVar8);
            uVar6 = 0x0007fc00 & (unsigned)((param_4+param_2)*0x400);
            local_34 = uVar6 | uVar5;
            pixel[0] = 2;
            pixel[1] = (unsigned char)(uVar6>>0x10);
            pixel[2] = (unsigned char)(local_34>>8);
            pixel[3] = (unsigned char)uVar5;
            pixel[4] = 0xff;
            uVar1 = *(unsigned char*)(iVar7+iVar9);
            *(unsigned char*)(iVar7+iVar9) = 0;
            FUN_000723b8(0x2000a060, uVar3, 0xffffffff, 0xffffffff);
            long long ret = (*(long long(**)(int,...))(*(int*)(iVar2+0x374)+8))(*(int*)(iVar2+0x374), iVar7, iVar9, (int)local_38, 1);
            iVar4 = (int)ret;
            FUN_00072558(0x2000a060);
            uVar3 = (unsigned)((u64)ret >> 32);
            if(iVar4 != 0 && 0 < *(volatile int*)0x2000230c){
                if(*(volatile int*)0x20007554 == 0){
                    DEBUG_PRINT(0x000d7383,0x000d7426);
                } else {
                    FUN_00019c70(0x000d7383, 0x000d7426);
                }
            }
            *(unsigned char*)(iVar7+iVar9) = uVar1;
            *(unsigned*)(iVar10+iVar8) = local_30;
            *(unsigned char*)(iVar7+4) = local_2c;
        }
        FUN_0007d77c(0x97);
        FUN_0007d772(1);
        uVar3 = 0;
    }
    return uVar3;
}
