/* Reconstructed FUN_000757b0 @ 0x757b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
typedef uint32_t u32;
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(u32,u32);
extern int FUN_00072040(u32);
extern void FUN_00072078(u32);
extern int FUN_0007205c(u32);
extern u32 FUN_000867da(void*,u32);
extern void FUN_000739f0(u32,u32);
static inline u32 rd_basepri(void){return __get_BASEPRI();}
static inline void wr_basepri_max(u32 v){__set_BASEPRI_MAX(v);}
static inline void wr_basepri(u32 v){__set_BASEPRI(v);}
static inline void isb_(void){__ISB();}
u32 FUN_000757b0(int* param_1, int param_2){
    u32 uVar7 = rd_basepri();
    wr_basepri_max(0x20);
    isb_();
    int iVar3 = FUN_00072040(0x2000b4a0);
    if(iVar3 != 0){
        FUN_00072078(0x2000b4a0);
        int* piVar4 = (int*)*param_1;
        param_1[3] = param_2;
        param_1[2] = 1;
        u32 uVar6;
        if(param_1 == piVar4){
            iVar3 = FUN_0007205c(0x2000b4a0);
            if(iVar3 == 0){
                FUN_0007e2fa(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0);
                FUN_0007e2fa(0x000f090b, 0x2000b4a0);
                FUN_0007e2ec(0x000f08c7, 0xf0);
                return 0;
            }
            wr_basepri(uVar7);
            isb_();
            uVar6 = 0;
        } else {
            int iVar3b = *piVar4;
            int* piVar5 = (int*)piVar4[1];
            *piVar5 = iVar3b;
            *(int**)(iVar3b+4) = piVar5;
            piVar4[0] = 0;
            piVar4[1] = 0;
            uVar6 = FUN_000867da(piVar4, 1);
            FUN_000739f0(0x2000b4a0, uVar7);
        }
        return uVar6;
    }
    FUN_0007e2fa(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72);
    FUN_0007e2fa(0x000f0935, 0x2000b4a0);
    FUN_0007e2ec(0x000f08c7, 0x72);
    return 0;
}
