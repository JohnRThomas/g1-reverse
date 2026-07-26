/* Reconstructed FUN_0004be0c @ 0x4be0c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
typedef uint32_t u32; typedef uint8_t u8;
typedef u32 (*fp)(u8*);
extern void FUN_0007e2fa(u32,u32,...);
extern void FUN_0007e2ec(u32,u32);
extern int FUN_00072040(int);
extern void FUN_00072078(int);
extern int FUN_0007205c(int);
extern u32 FUN_0007e35c(int,u32,u32);
extern void FUN_0007e4f2(int);
void FUN_0004be0c(int param_1, u8* param_2){
    u32 uVar3 = (*(fp*)(param_1+0x1c))(param_2);
    int iVar5 = param_1+0x14;
    u32 uVar6 = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20);
    __ISB();
    int iVar4 = FUN_00072040(iVar5);
    if(iVar4==0){
        FUN_0007e2fa(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72);
        FUN_0007e2fa(0x000f0935, iVar5);
        uVar3=0x72;
    } else {
        FUN_00072078(iVar5);
        *param_2 = *param_2 | 1;
        uVar3 = FUN_0007e35c(param_1, *(u32*)(param_1+4), uVar3);
        *(u32*)(param_1+4) = uVar3;
        FUN_0007e4f2(param_1);
        iVar4 = FUN_0007205c(iVar5);
        if(iVar4!=0){
            __set_BASEPRI(uVar6);
            __ISB();
            return;
        }
        FUN_0007e2fa(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0);
        FUN_0007e2fa(0x000f090b, iVar5);
        uVar3=0xf0;
    }
    FUN_0007e2ec(0x000f08c7, uVar3);
}
