/* Reconstructed FUN_00072f28 @ 0x72f28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
typedef uint32_t u32;
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(u32,u32);
extern int FUN_00072040(u32);
extern void FUN_00072078(u32);
extern int FUN_0007205c(u32);
extern u32 FUN_00072cd4(int,void*);
static inline u32 rd_basepri(void){return __get_BASEPRI();}
static inline void wr_basepri_max(u32 v){__set_BASEPRI_MAX(v);}
static inline void wr_basepri(u32 v){__set_BASEPRI(v);}
static inline void isb_(void){__ISB();}
u32 FUN_00072f28(u32 param_1, int param_2, u32 param_3){
    struct lookup_key {
        u32 value;
        u32 qualifier;
    } key = { param_1, param_3 };
    u32 uVar4, uVar5;
    if(param_2==0){
        FUN_0007e2fa(0x00099cbd, 0x000f82e0, 0x000f820f, 0x174, param_1);
        FUN_0007e2ec(0x000f820f, 0x174);
    }

retry:
    uVar5 = rd_basepri();
    wr_basepri_max(0x20);
    isb_();
    {
        int iVar3 = FUN_00072040(0x2000b480);
        if(iVar3==0){
            FUN_0007e2fa(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72, param_1);
            FUN_0007e2fa(0x000f0935, 0x2000b480);
            FUN_0007e2ec(0x000f08c7, 0x72);
            goto retry;
        }
        FUN_00072078(0x2000b480);
        uVar4 = FUN_00072cd4(param_2, &key);
        iVar3 = FUN_0007205c(0x2000b480);
        if(iVar3!=0){
            wr_basepri(uVar5);
            isb_();
            return uVar4;
        }
        FUN_0007e2fa(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0, param_1);
        FUN_0007e2fa(0x000f090b, 0x2000b480);
        FUN_0007e2ec(0x000f08c7, 0xf0);
        goto retry;
    }
}
