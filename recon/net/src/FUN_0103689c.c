/* net-core FUN_0103689c @ 0x103689c  (parity 300 trials PROVEN) */

static inline int isCurrentModePrivileged(void){return 1;}
static inline int getBasePriority(void){return 0;}
static inline void setBasePriority(int p){(void)p;}
static inline void InstructionSynchronizationBarrier(int x){(void)x; __atomic_signal_fence(__ATOMIC_SEQ_CST);}
static inline unsigned int readIPSR(void){return 0;}

extern int FUN_0103610c(void *);
extern int FUN_01036128(void *);
extern void FUN_01036144(void *);
extern int FUN_010375b8(void*, unsigned int, void*, unsigned int, unsigned int, unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);

int FUN_0103689c(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int ipsr = readIPSR();
    if (ipsr == 0 || (param_3 | param_4) == 0) {
        unsigned int uVar5 = 0;
        if (isCurrentModePrivileged()) {
            uVar5 = getBasePriority();
        }
        if (isCurrentModePrivileged()) {
            unsigned int uVar4b = getBasePriority();
            if (uVar4b == 0 || uVar4b > 0x40) {
                setBasePriority(0x40);
            }
        }
        InstructionSynchronizationBarrier(0xf);

        volatile int * const p54 = (volatile int *)0x21004b4c;
        int iVar2 = FUN_0103610c((void*)p54);
        if (iVar2 == 0) {
            FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0x72);
            FUN_01039bb0(0x0103d3b6, 0x72);
            __builtin_unreachable();
        }

        FUN_01036144((void*)p54);

        if (*(volatile int *)(param_1 + 8) == 0) {
            if ((param_3 | param_4) != 0) {
                return FUN_010375b8((void*)p54, uVar5, (void*)param_1, param_3 | param_4, param_3, param_4);
            }
            int iVar2b = FUN_01036128((void*)p54);
            if (iVar2b != 0) {
                if (isCurrentModePrivileged()) {
                    setBasePriority((int)uVar5);
                }
                InstructionSynchronizationBarrier(0xf);
                return 0xfffffff0;
            }
        } else {
            *(volatile int *)(param_1 + 8) = *(volatile int *)(param_1 + 8) - 1;
            int iVar2c = FUN_01036128((void*)p54);
            if (iVar2c != 0) {
                if (isCurrentModePrivileged()) {
                    setBasePriority((int)uVar5);
                }
                InstructionSynchronizationBarrier(0xf);
                return 0;
            }
        }

        FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0xf0);
        FUN_01039bb0(0x0103d3b6, 0xf0);
        __builtin_unreachable();
    } else {
        FUN_01039bbe(0x0103d2a7, 0x0103eacd, 0x80);
        FUN_01039bb0(0x0103eacd, 0x80);
        __builtin_unreachable();
    }
}
