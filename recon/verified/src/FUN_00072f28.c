/* Reconstructed FUN_00072f28 @ 0x72f28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
extern void FUN_0007e2fa(u32,u32,...);
extern void FUN_0007e2ec(u32,u32);
extern int FUN_00072040(u32);
extern void FUN_00072078(u32);
extern int FUN_0007205c(u32);
extern u32 FUN_00072cd4(int,void*);
static inline u32 rd_basepri(void){u32 v;__asm__ volatile("mrs %0, basepri":"=r"(v));return v;}
static inline void wr_basepri_max(u32 v){__asm__ volatile("msr basepri_max, %0"::"r"(v):"memory");}
static inline void wr_basepri(u32 v){__asm__ volatile("msr basepri, %0"::"r"(v):"memory");}
static inline void isb_(void){__asm__ volatile("isb");}
u32 FUN_00072f28(u32 param_1, int param_2, u32 param_3){
    u32 local_14 = param_1;
    u32 uStack_10 = param_3;
    (void)uStack_10;
    u32 uVar4, uVar5;
    if(param_2==0){
        FUN_0007e2fa(0x00099cbd, 0x000f82e0, 0x000f820f, 0x174, param_1);
        uVar4=0x174; uVar5=0x000f820f;
    } else {
        uVar5 = rd_basepri();
        wr_basepri_max(0x20);
        isb_();
        int iVar3 = FUN_00072040(0x2000b480);
        if(iVar3==0){
            FUN_0007e2fa(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72, param_1);
            FUN_0007e2fa(0x000f0935, 0x2000b480);
            uVar4=0x72; uVar5=0x000f08c7;
        } else {
            FUN_00072078(0x2000b480);
            uVar4 = FUN_00072cd4(param_2, &local_14);
            iVar3 = FUN_0007205c(0x2000b480);
            if(iVar3!=0){
                wr_basepri(uVar5);
                isb_();
                return uVar4;
            }
            FUN_0007e2fa(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0, param_1);
            FUN_0007e2fa(0x000f090b, 0x2000b480);
            uVar4=0xf0; uVar5=0x000f08c7;
        }
    }
    FUN_0007e2ec(uVar5, uVar4);
    return 0;
}

