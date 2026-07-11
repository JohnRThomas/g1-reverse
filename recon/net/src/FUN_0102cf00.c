/* net-core FUN_0102cf00 @ 0x102cf00  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef unsigned int uint;
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline int isCurrentModePrivileged(void){return (__get_CONTROL()&1)==0;}
static inline int getBasePriority(void){return (int)__get_BASEPRI();}
static inline void setBasePriority(int p){__set_BASEPRI((unsigned)p);}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__ISB();}

extern int FUN_0103610c(int);
extern int FUN_01036128(int);
extern void FUN_01036144(int);
extern void thunk_FUN_01036824(int);
extern void FUN_01039bb0(unsigned int,unsigned int);
extern void FUN_01039bbe(unsigned int,unsigned int,unsigned int);
extern unsigned int FUN_01039c20(int,int,int);
extern void FUN_01039c3c(int,int);

void FUN_0102cf00(int param_1, unsigned int *param_2)
{
    int (*cb)(unsigned int*) = *(volatile int(**)(unsigned int*))(param_1 + 0x1c);
    int iVar3 = cb(param_2);
    int iVar6 = param_1 + 0x14;
    unsigned int uVar7 = 0;
    if (isCurrentModePrivileged()) uVar7 = getBasePriority();
    if (isCurrentModePrivileged()) {
        unsigned int uVar2 = getBasePriority();
        if (uVar2 == 0 || uVar2 > 0x40) setBasePriority(0x40);
    }
    InstructionSynchronizationBarrier(0xf);
    int iVar4 = FUN_0103610c(iVar6);
    if (iVar4 == 0) {
        FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0x72);
        FUN_01039bb0(0x0103d3b6, 0x72);
        __builtin_unreachable();
    } else {
        FUN_01036144(iVar6);
        *(volatile unsigned char*)param_2 = (*(volatile unsigned char*)param_2) & 0xfe;
        if ((int)(*(volatile int*)(param_1 + 0x10) << 0x1e) < 0 &&
            param_2 != (unsigned int*)(*(volatile int*)(param_1 + 0x20) + *(volatile int*)(param_1 + 0xc) * 4)) {
            *param_2 = (*param_2 & 3) | (iVar3 << 2);
        } else {
            *(volatile unsigned char*)param_2 = (*(volatile unsigned char*)param_2) & 0xfd;
            if (*(volatile int*)(param_1 + 0xc) == *(volatile int*)(param_1 + 8)) {
                unsigned int uVar5 = FUN_01039c20(param_1, *(volatile int*)(param_1 + 0xc), iVar3);
                *(volatile unsigned int*)(param_1 + 8) = uVar5;
            }
            FUN_01039c3c(param_1, iVar3);
        }
        int iVar3b = FUN_01036128(iVar6);
        if (iVar3b != 0) {
            if (isCurrentModePrivileged()) setBasePriority(uVar7);
            InstructionSynchronizationBarrier(0xf);
            thunk_FUN_01036824(param_1 + 0x2c);
            return;
        }
        FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0xf0);
        FUN_01039bb0(0x0103d3b6, 0xf0);
        __builtin_unreachable();
    }
}
