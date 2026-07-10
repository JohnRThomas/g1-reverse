/* Reconstructed FUN_00072908 @ 0x72908  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072040(uint32_t);
extern int FUN_0007205c(uint32_t);
extern void FUN_00072078(uint32_t);
extern int FUN_00073f6c(uint32_t,uint32_t,int,uint32_t,uint32_t,uint32_t);
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,...);

int FUN_00072908(int param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
    uint32_t ipsr, bp, v; int iVar2; int r3;
    __asm__ volatile("mrs %0, ipsr":"=r"(ipsr));
    if (ipsr != 0 && (param_3 | param_4) != 0){
        FUN_0007e2fa(0x00099cbd,0x000f81b8,0x000f8198,0x80,(uint32_t)param_1,param_2,param_3);
        FUN_0007e2fa(0x000f53ff);
        FUN_0007e2ec(0x000f8198,0x80);
        goto L936;
    }
  L936:
    __asm__ volatile("mrs %0, basepri":"=r"(bp));
    v = 0x20;
    __asm__ volatile("msr basepri_max, %0"::"r"(v));
    __asm__ volatile("isb sy");
    iVar2 = FUN_00072040(0x2000b474);
    if (iVar2 == 0){
        FUN_0007e2fa(0x00099cbd,0x000f0920,0x000f08c7,0x72,(uint32_t)param_1,param_2,param_3);
        FUN_0007e2fa(0x000f0935,0x2000b474);
        FUN_0007e2ec(0x000f08c7,0x72);
        goto L936;
    }
    FUN_00072078(0x2000b474);
    r3 = *(volatile int*)(param_1+8);
    if (r3 == 0){
        if ((param_3 | param_4) != 0){
            return FUN_00073f6c(0x2000b474, bp, param_1, param_3|param_4, param_3, param_4);
        }
        iVar2 = FUN_0007205c(0x2000b474);
        if (iVar2 != 0){
            __asm__ volatile("msr basepri, %0"::"r"(bp));
            __asm__ volatile("isb sy");
            return 0xfffffff0;
        }
    } else {
        *(volatile int*)(param_1+8) = r3 - 1;
        iVar2 = FUN_0007205c(0x2000b474);
        if (iVar2 != 0){
            __asm__ volatile("msr basepri, %0"::"r"(bp));
            __asm__ volatile("isb sy");
            return 0;
        }
    }
    FUN_0007e2fa(0x00099cbd,0x000f08f4,0x000f08c7,0xf0,(uint32_t)param_1,param_2,param_3);
    FUN_0007e2fa(0x000f090b,0x2000b474);
    FUN_0007e2ec(0x000f08c7,0xf0);
    goto L936;
}

