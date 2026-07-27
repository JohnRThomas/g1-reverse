/* Reconstructed FUN_00073518 @ 0x73518  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
typedef uint32_t u32;
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(u32,u32);
extern int FUN_00072040(u32);
extern void FUN_00072078(u32);
extern int FUN_0007205c(u32);
extern void FUN_0008656a(int);
extern u32 FUN_00086596(int);
u32 FUN_00073518(int param_1, u32 param_2, u32 param_3, u32 param_4){
    u32 uVar4, uVar5;
    if(param_1==0){
        FUN_0007e2fa(0x00099cbd, 0x000f82df, 0x000f820f, 0x400, param_4);
        FUN_0007e2ec(0x000f820f, 0x400);
    }
    {
        uVar5 = __get_BASEPRI();
        __set_BASEPRI_MAX(0x20);
        __ISB();
        int iVar3 = FUN_00072040(0x2000b480);
        if(iVar3==0){
            FUN_0007e2fa(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72, param_4);
            FUN_0007e2fa(0x000f0935, 0x2000b480);
            uVar4=0x72; uVar5=0x000f08c7;
        } else {
            FUN_00072078(0x2000b480);
            FUN_0008656a(param_1);
            uVar4 = FUN_00086596(param_1);
            iVar3 = FUN_0007205c(0x2000b480);
            if(iVar3!=0){
                __set_BASEPRI(uVar5);
                __ISB();
                return uVar4;
            }
            FUN_0007e2fa(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0);
            FUN_0007e2fa(0x000f090b, 0x2000b480);
            uVar4=0xf0; uVar5=0x000f08c7;
        }
    }
    FUN_0007e2ec(uVar5, uVar4);
    return 0;
}
