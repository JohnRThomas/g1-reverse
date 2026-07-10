/* Reconstructed FUN_0005a1b0 @ 0x5a1b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
typedef void (*fp)(u32,void*,int,int);
typedef void (*jp)(u32,int,u32*);
extern void FUN_000826f6(u32*,u32);
extern int FUN_00059c70(u32);
extern void FUN_000828e8(u32,int,u32*,u32*);
extern void FUN_00082a42(u32,int,void*);
void FUN_0005a1b0(u32 param_1,int param_2,u32 param_3,u32 param_4,u32* param_5){
    FUN_000826f6(param_5+5, 0xfffffffb);
    if(param_2 == 0){
        if(*(short*)((char*)param_5+0x10) == 0){
            (*(fp)(uintptr_t)*param_5)(param_1, param_5, param_2, param_2);
        }
    } else {
        int iVar1 = FUN_00059c70(param_1);
        if(iVar1 == 0) return;
        u32* puVar3 = *(u32**)(iVar1+8);
        if(puVar3 != 0){
            u32* puVar2 = (u32*)*puVar3;
            while(puVar3 != 0){
                if(puVar3 == param_5+6){
                    FUN_000828e8(param_1, iVar1, puVar2, param_5);
                    break;
                }
                puVar3 = puVar2;
                if(puVar2 != 0) puVar2 = (u32*)*puVar2;
            }
        }
    }
    jp JUMP = (jp)(uintptr_t)param_5[1];
    if(JUMP == 0){
        if(param_5[2] == 0) return;
        u32 local[2]; local[0]=2; local[1]=0x000f4812;
        FUN_00082a42(0x00088128, 0x1080, local);
        JUMP = (jp)(uintptr_t)param_5[2];
        param_5 = 0;
    }
    JUMP(param_1, param_2, param_5);
}

