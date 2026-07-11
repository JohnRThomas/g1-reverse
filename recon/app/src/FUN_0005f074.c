/* Reconstructed FUN_0005f074 @ 0x5f074  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern int FUN_00072040(void*);
extern int FUN_0007205c(void*);
extern void FUN_00072078(void*);
extern void FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned,...);

void FUN_0005f074(uint32_t *param_1, uint32_t *param_2){
    if (param_1 == 0){
        FUN_0007e2fa(0x00099cbd,0x000f3630,0x000f539a,0x1ad);
        FUN_0007e2ec(0x000f539a,0x1ad);
    } else if (param_2 == 0){
        FUN_0007e2fa(0x00099cbd,0x000f45be,0x000f539a,0x1ae);
        FUN_0007e2ec(0x000f539a,0x1ae);
    }

retry:
    {
        unsigned saved_priority = __get_BASEPRI();
        int iVar4;
        __set_BASEPRI_MAX(0x20);
        __ISB();
        iVar4 = FUN_00072040((void*)0x2000b004);
        if (iVar4==0) {
            FUN_0007e2fa(0x00099cbd,0x000f0920,0x000f08c7,0x72);
            FUN_0007e2fa(0x000f0935,0x2000b004);
            FUN_0007e2ec(0x000f08c7,0x72);
            goto retry;
        }
        FUN_00072078((void*)0x2000b004);
        *param_2 = 0;
        if (param_1[1]==0){
            param_1[0] = (uint32_t)param_2;
            param_1[1] = (uint32_t)param_2;
        } else {
            *((uint32_t*)param_1[1]) = (uint32_t)param_2;
            param_1[1] = (uint32_t)param_2;
        }
        iVar4 = FUN_0007205c((void*)0x2000b004);
        if (iVar4 != 0){
            __set_BASEPRI(saved_priority);
            __ISB();
            return;
        }
        FUN_0007e2fa(0x00099cbd,0x000f08f4,0x000f08c7,0xf0);
        FUN_0007e2fa(0x000f090b,0x2000b004);
        FUN_0007e2ec(0x000f08c7,0xf0);
        goto retry;
    }
}
