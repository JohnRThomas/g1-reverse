#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010375b8 @ 0x010375b8
 * public-name: FUN_010375b8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eb0e                           @ 0x0103eb0e
 *   g_zephyr_sched_swap_tmp                  @ 0x21004b5c
 */
/* net-core FUN_010375b8 @ 0x10375b8  (parity 300 trials PROVEN) */
/* net-core FUN_010375b8 @ 0x10375b8  (parity 300 trials PROVEN) */

#ifdef G1_COHESIVE_BUILD
/* P4 iteration 20 - the shipped CPUNET `_kernel` is at 0x21004b28.
 * In the relocated cohesive link that address is inside `sdc_mempool`
 * (0x21002bb8..0x21007e79), so every recovered kernel body that reaches the
 * scheduler through this base read/wrote a SHADOW copy of `_kernel` carved out
 * of the SoftDevice Controller's heap while the linked Zephyr scheduler
 * (z_arm_pendsv, arch_swap, z_ready_thread) used the real one at
 * &_kernel.  Iteration 7 converted only the four spinlock validators and
 * recorded the rest as open; this pass closes the whole window structurally.
 * Field offsets are identical in both images: +0x08 = cpus[0].current and
 * +0x10 = cpus[0].id were verified against the shipped disassembly in
 * iteration 7, which fixes struct _cpu at 0x14 bytes and therefore
 * ready_q.cache at +0x14 and ready_q.runq at +0x18; `nm -S` reports
 * sizeof(_kernel) = 0x20 in this link.
 * Parity builds keep the original literal, so no proven body changes. */
/* Reached through an asm label so no reconstruction TU has to pull in the
 * Zephyr kernel headers (several of them declare assert_print /
 * assert_post_action with the recovered prototypes). */
extern char g1_net_kernel_object[] __asm__("_kernel");
#define G1_NET_KERNEL_BASE ((unsigned long)g1_net_kernel_object)
#else
#define G1_NET_KERNEL_BASE 0x21004b28ul
#endif
#define G1_NET_K(off) (G1_NET_KERNEL_BASE + (off))

typedef unsigned int uint;
static inline int isCurrentModePrivileged(void){return 1;}
static inline int getBasePriority(void){return 0;}
static inline void setBasePriority(int p){(void)p;}
static inline void InstructionSynchronizationBarrier(int x){(void)x; __atomic_signal_fence(__ATOMIC_SEQ_CST);}

extern void FUN_0102ec10(unsigned int);
extern int FUN_0103610c(int,int,int,int);
extern int FUN_01036128(int);
extern void FUN_01036144(int);
extern void FUN_01037588(unsigned int,unsigned int,unsigned int,unsigned int);
extern void assert_post_action(unsigned int,unsigned int);
extern void assert_print(unsigned int,unsigned int,unsigned int);

void FUN_010375b8(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4,
                   unsigned int param_5, unsigned int param_6)
{
    volatile int * const p_1037658 = (volatile int *)G1_NET_K(0x00);
    volatile int * const p_103765c = (volatile int *)0x21004b68;
    volatile int * const p_1037660 = (volatile int *)((unsigned long)&g_zephyr_sched_swap_tmp) /*=0x21004b5c*/;
    int iVar2 = (int)(unsigned int)p_103765c;
    int iVar4 = (int)(unsigned int)p_1037658;
    int bVar7 = (param_1 == iVar2);
    *p_1037660 = *(volatile int *)(iVar4 + 8);
    unsigned int uVar6;
    if (bVar7) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0x35f);
        assert_post_action(((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0x35f);
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
            assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
            assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
            __builtin_unreachable();
        } else {
            FUN_01036144(iVar2);
            FUN_01037588(*(volatile unsigned int *)(iVar4 + 8), param_3, param_5, param_6);
            int iVar4b = FUN_01036128(param_1);
            if (iVar4b != 0 && FUN_01036128(iVar2) != 0) {
                FUN_0102ec10(param_2);
                return;
            }
            assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x111);
            assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x111);
            __builtin_unreachable();
        }
    }
}
