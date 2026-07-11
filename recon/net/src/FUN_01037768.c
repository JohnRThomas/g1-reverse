/* net-core FUN_01037768 @ 0x1037768  (parity 300 trials PROVEN) */

static inline int isCurrentModePrivileged(void){return 1;}
static inline int getBasePriority(void){return 0;}
static inline void setBasePriority(int p){(void)p;}
static inline void InstructionSynchronizationBarrier(int x){(void)x; __atomic_signal_fence(__ATOMIC_SEQ_CST);}

extern int FUN_0103610c(void *);
extern int FUN_01036128(void *);
extern void FUN_01036144(void *);
extern void FUN_01036f74(int);
extern void FUN_0103735c(unsigned int, int);
extern void FUN_010380d8(int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern void FUN_0103b29c(unsigned int);

void FUN_01037768(int param_1)
{
    FUN_010380d8(param_1 + 0x18);

    unsigned int uVar6 = 0;
    if (isCurrentModePrivileged()) {
        uVar6 = getBasePriority();
    }
    if (isCurrentModePrivileged()) {
        unsigned int uVar2 = getBasePriority();
        if (uVar2 == 0 || uVar2 > 0x40) {
            setBasePriority(0x40);
        }
    }
    InstructionSynchronizationBarrier(0xf);

    volatile int * const p1800 = (volatile int *)0x21004b68;
    int iVar4v = FUN_0103610c((void *)p1800);
    if (iVar4v == 0) {
        FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0x72);
        FUN_01039bb0(0x0103d3b6, 0x72);
        __builtin_unreachable();
    }

    FUN_01036144((void *)p1800);
    volatile signed char *pb = (volatile signed char *)param_1;
    if (pb[0xd] < 0) {
        ((volatile unsigned char *)param_1)[0xd] = ((volatile unsigned char *)param_1)[0xd] & 0x7f;
        FUN_0103735c(0x21004b40, param_1);
    }

    volatile int * const p1810 = (volatile int *)0x21004b28;
    int iVar5 = p1810[2];
    ((volatile unsigned char *)param_1)[0xd] = ((volatile unsigned char *)param_1)[0xd] | 0x10;
    FUN_01036f74(iVar5 == param_1);

    int iVar5b = FUN_01036128((void *)p1800);
    if (iVar5b != 0) {
        if (isCurrentModePrivileged()) {
            setBasePriority((int)uVar6);
        }
        InstructionSynchronizationBarrier(0xf);
        if (p1810[2] != param_1) {
            return;
        }
        uVar6 = 0;
        if (isCurrentModePrivileged()) {
            uVar6 = getBasePriority();
        }
        if (isCurrentModePrivileged()) {
            unsigned int uVar2 = getBasePriority();
            if (uVar2 == 0 || uVar2 > 0x40) {
                setBasePriority(0x40);
            }
        }
        InstructionSynchronizationBarrier(0xf);
        FUN_0103b29c(uVar6);
        return;
    }
    FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0xf0);
    FUN_01039bb0(0x0103d3b6, 0xf0);
    __builtin_unreachable();
}
