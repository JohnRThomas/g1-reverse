/* net-core FUN_010375b8 @ 0x10375b8  (parity 300 trials PROVEN) */
/* net-core FUN_010375b8 @ 0x10375b8  (parity 300 trials PROVEN) */

typedef unsigned int uint;
static inline int isCurrentModePrivileged(void){unsigned c;__asm__ volatile("mrs %0, control":"=r"(c));return (c&1)==0;}
static inline int getBasePriority(void){unsigned b;__asm__ volatile("mrs %0, basepri":"=r"(b));return (int)b;}
static inline void setBasePriority(int p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__asm__ volatile("isb":::"memory");}

extern void FUN_0102ec10(unsigned int);
extern int FUN_0103610c(int,int,int,int);
extern int FUN_01036128(int);
extern void FUN_01036144(int);
extern void FUN_01037588(unsigned int,unsigned int,unsigned int,unsigned int);
extern void FUN_01039bb0(unsigned int,unsigned int);
extern void FUN_01039bbe(unsigned int,unsigned int,unsigned int);

void FUN_010375b8(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4,
                   unsigned int param_5, unsigned int param_6)
{
    volatile int * const p_1037658 = (volatile int *)0x21004b28;
    volatile int * const p_103765c = (volatile int *)0x21004b68;
    volatile int * const p_1037660 = (volatile int *)0x21004b5c;
    int iVar2 = *p_103765c;
    int iVar4 = *p_1037658;
    int bVar7 = (param_1 == iVar2);
    *p_1037660 = *(volatile int *)(iVar4 + 8);
    unsigned int uVar6;
    if (bVar7) {
        FUN_01039bbe(0x0103d2a7, 0x0103eb0e, 0x35f);
        FUN_01039bb0(0x0103eb0e, 0x35f);
        __builtin_unreachable();
    } else {
        uVar6 = 0;
        if (isCurrentModePrivileged()) {
            uVar6 = getBasePriority();
        }
        if (isCurrentModePrivileged()) {
            unsigned int uVar1 = getBasePriority();
            if (uVar1 == 0 || uVar1 > 0x40) {
                setBasePriority(0x40);
            }
        }
        InstructionSynchronizationBarrier(0xf);
        int iVar3 = FUN_0103610c(iVar2, param_2, 0x40, uVar6);
        if (iVar3 == 0) {
            FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0x72);
            FUN_01039bb0(0x0103d3b6, 0x72);
            __builtin_unreachable();
        } else {
            FUN_01036144(iVar2);
            FUN_01037588(*(volatile unsigned int *)(iVar4 + 8), param_3, param_5, param_6);
            int iVar4b = FUN_01036128(param_1);
            if (iVar4b != 0 && FUN_01036128(iVar2) != 0) {
                FUN_0102ec10(param_2);
                return;
            }
            FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0x111);
            FUN_01039bb0(0x0103d3b6, 0x111);
            __builtin_unreachable();
        }
    }
}


