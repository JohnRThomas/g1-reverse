/* Reconstructed FUN_00047260 @ 0x47260  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_000723b8(int,...);
extern int FUN_00072558(int,...);
extern long long FUN_0007d4ec(void);
extern int FUN_0007d772(int,...);
extern int FUN_0007d77c(int,...);

unsigned FUN_00047260(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)
{
    unsigned char uVar1; int iVar2; unsigned uVar3; int iVar4; unsigned uVar5,uVar6;
    unsigned lock_arg;
    int iVar7,iVar8,iVar9,iVar10;
    unsigned char local_38[4]; unsigned local_34; unsigned local_30; unsigned char local_2c;

    local_38[0] = 0;
    {
        unsigned long long context_result = (unsigned long long)FUN_0007d4ec();
        iVar2 = (int)context_result;
        lock_arg = (unsigned)(context_result >> 32);
    }
    if(*(int*)(iVar2+0x35c) == 0){
        if(0 < *(volatile int*)0x2000230c){
            if(*(volatile int*)0x20007554 == 0){
                DEBUG_PRINT(0x000aa891, 0x000d7441);
            } else { FUN_00019c70(0x000aa891, 0x000d7441); }
        }
        uVar3 = 0xffffffff;
    } else {
        if(199 < param_6) param_6 = 200;
        if(0x27f < param_5) param_5 = 0x280;
        iVar7 = (5 - param_3/2) + param_5/2;
        uVar5 = (param_3 + param_1) & 0x3ff;
        for(; param_4 <= param_6; param_4 = param_4 + 1){
            iVar10 = *(int*)(iVar2+0x344);
            iVar9 = param_4*0x140 + param_3/2 - 5;
            iVar8 = iVar10 + iVar9;
            volatile unsigned char *pixel = (volatile unsigned char *)iVar8;
            local_2c = *(unsigned char*)(iVar8+4);
            local_30 = *(unsigned*)(iVar10+iVar9);
            uVar6 = 0x0007fc00 & (unsigned)((param_2+param_4)*0x400);
            local_34 = uVar6 | uVar5;
            pixel[0] = 2;
            pixel[1] = (unsigned char)(uVar6>>0x10);
            pixel[2] = (unsigned char)(local_34>>8);
            pixel[3] = (unsigned char)uVar5;
            pixel[4] = 0xff;
            uVar1 = *(unsigned char*)(iVar8+iVar7);
            *(unsigned char*)(iVar8+iVar7) = 0;
            FUN_000723b8(0x2000a060, lock_arg, -1, -1);
            iVar4 = (*(int(**)(int,...))(*(int*)(iVar2+0x374)+8))(*(int*)(iVar2+0x374), iVar8, iVar7, (int)local_38, 1);
            FUN_00072558(0x2000a060);
            if(iVar4 != 0 && 0 < *(volatile int*)0x2000230c){
                if(*(volatile int*)0x20007554 == 0){
                    DEBUG_PRINT(0x000d7383, 0x000d7441);
                } else { FUN_00019c70(0x000d7383, 0x000d7441); }
            }
            *(unsigned char*)(iVar8+iVar7) = uVar1;
            *(unsigned*)(iVar10+iVar9) = local_30;
            *(unsigned char*)(iVar8+4) = local_2c;
        }
        FUN_0007d77c(0x97);
        FUN_0007d772(1);
        uVar3 = 0;
    }
    return uVar3;
}
