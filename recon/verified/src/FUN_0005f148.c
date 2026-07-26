/* Reconstructed FUN_0005f148 @ 0x5f148  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
typedef uint32_t u32;
extern void FUN_0007e2fa(u32,u32,...);
extern void FUN_0007e2ec(u32,u32);
extern int FUN_00072040(u32);
extern void FUN_00072078(u32);
extern int FUN_0007205c(u32);
static inline u32 rd_basepri(void){ return __get_BASEPRI(); }
static inline void wr_basepri_max(u32 v){ __set_BASEPRI_MAX(v); }
static inline void wr_basepri(u32 v){ __set_BASEPRI(v); }
static inline void isb_(void){ __ISB(); }
u32* FUN_0005f148(u32* param_1){
    u32 uVar4, uVar6;
    if(param_1 == 0){
        FUN_0007e2fa(0x00099cbd, 0x000f3630, 0x000f539a, 0x1ba);
        uVar4=0x1ba; uVar6=0x000f539a;
    } else {
        uVar6 = rd_basepri();
        wr_basepri_max(0x20);
        isb_();
        int iVar3 = FUN_00072040(0x2000b004);
        if(iVar3==0){
            FUN_0007e2fa(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72);
            FUN_0007e2fa(0x000f0935, 0x2000b004);
            uVar4=0x72; uVar6=0x000f08c7;
        } else {
            FUN_00072078(0x2000b004);
            u32* puVar5 = (u32*)*param_1;
            if(puVar5 != 0){
                uVar4 = *puVar5;
                *param_1 = uVar4;
                if(puVar5 == (u32*)param_1[1]) param_1[1] = uVar4;
            }
            iVar3 = FUN_0007205c(0x2000b004);
            if(iVar3!=0){
                wr_basepri(uVar6);
                isb_();
                return puVar5;
            }
            FUN_0007e2fa(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0);
            FUN_0007e2fa(0x000f090b, 0x2000b004);
            uVar4=0xf0; uVar6=0x000f08c7;
        }
    }
    FUN_0007e2ec(uVar6, uVar4);
    return 0;
}
