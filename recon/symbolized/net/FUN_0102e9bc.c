#include "g1_net_symbols.h"
/* net-core FUN_0102e9bc @ 0x102e9bc  (parity 300 trials PROVEN) */

#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline int isCurrentModePrivileged(void){return (__get_CONTROL()&1)==0;}
static inline void setBasePriority(int p){__set_BASEPRI((unsigned)p);}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__ISB();}
static inline void DataSynchronizationBarrier(int x){(void)x;__DSB();}
static inline void WaitForInterrupt(void){__WFI();}
static inline void disableIRQinterrupts(void){__disable_irq();}
static inline void enableIRQinterrupts(void){__enable_irq();}

extern void FUN_0102d0c4(void);
extern int FUN_0102d1c0(void);

unsigned int FUN_0102e9bc(void)
{
    int bVar1;
    int iVar2;

    FUN_0102d0c4();
    disableIRQinterrupts();
    bVar1 = isCurrentModePrivileged();
    if (bVar1) {
        setBasePriority(0);
    }
    InstructionSynchronizationBarrier(0xf);
    iVar2 = FUN_0102d1c0();
    if (iVar2 != 0) {
        DataSynchronizationBarrier(0xf);
        WaitForInterrupt();
    }
    enableIRQinterrupts();
    InstructionSynchronizationBarrier(0xf);
    return 0;
}
