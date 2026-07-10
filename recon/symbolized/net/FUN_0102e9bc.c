#include "g1_net_symbols.h"
/* net-core FUN_0102e9bc @ 0x102e9bc  (parity 300 trials PROVEN) */
/* net-core FUN_0102e9bc @ 0x102e9bc  (parity 300 trials PROVEN) */
/* net-core FUN_0102e9bc @ 0x102e9bc  (parity 300 trials PROVEN) */
/* net-core FUN_0102e9bc @ 0x102e9bc  (parity 300 trials PROVEN) */

static inline int isCurrentModePrivileged(void){unsigned c;__asm__ volatile("mrs %0, control":"=r"(c));return (c&1)==0;}
static inline void setBasePriority(int p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__asm__ volatile("isb":::"memory");}
static inline void DataSynchronizationBarrier(int x){(void)x;__asm__ volatile("dsb":::"memory");}
static inline void WaitForInterrupt(void){__asm__ volatile("wfi":::"memory");}
static inline unsigned int disableIRQinterrupts(void){unsigned p;__asm__ volatile("mrs %0, primask":"=r"(p));__asm__ volatile("cpsid i":::"memory");return p;}
static inline void enableIRQinterrupts(void){__asm__ volatile("cpsie i":::"memory");}

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




