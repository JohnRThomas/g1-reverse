#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01036774 @ 0x01036774
 * public-name: FUN_01036774
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* net-core FUN_01036774 @ 0x1036774  (parity 300 trials PROVEN) */

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

static inline int isCurrentModePrivileged(void){return 1;}
static inline int getBasePriority(void){return 0;}
static inline void setBasePriority(int p){(void)p;}
static inline void InstructionSynchronizationBarrier(int x){(void)x; __atomic_signal_fence(__ATOMIC_SEQ_CST);}

extern int FUN_0103610c(void *);
extern int FUN_01036128(void *);
extern void FUN_01036144(void *);
extern int FUN_010375b8(void*, unsigned int, void*, unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int);
extern unsigned int FUN_0103b1e2(void*, unsigned int, void*, unsigned int, void*, unsigned int);

unsigned int FUN_01036774(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int *puVar7 = param_1 + 2;
    unsigned int uVar8 = 0;
    if (isCurrentModePrivileged()) {
        uVar8 = getBasePriority();
    }
    if (isCurrentModePrivileged()) {
        unsigned int uVar5 = getBasePriority();
        if (uVar5 == 0 || uVar5 > 0x40) {
            setBasePriority(0x40);
        }
    }
    InstructionSynchronizationBarrier(0xf);

    int iVar2 = FUN_0103610c(puVar7);
    if (iVar2 == 0) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
        uVar8 = 0x72;
        assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, uVar8);
        __builtin_unreachable();
    }

    FUN_01036144(puVar7);
    unsigned int *puVar6 = (unsigned int *)param_1[0];
    unsigned int uVar3 = 0;
    if (puVar6 == 0) {
        if ((param_3 | param_4) != 0) {
            int r = FUN_010375b8(puVar7, uVar8, param_1 + 3, param_3 | param_4, param_3, param_4, param_3);
            if (r != 0) {
                return 0;
            }
            volatile unsigned int * const p1 = (volatile unsigned int *)G1_NET_K(0x00);
            unsigned int inner = p1[2];
            unsigned int val = *(volatile unsigned int *)(inner + 0x14);
            return val;
        }
    } else {
        unsigned int *puVar4 = (unsigned int *)param_1[1];
        unsigned int uVar5b = (*puVar6) & 0xfffffffc;
        param_1[0] = uVar5b;
        if (puVar6 == puVar4) {
            param_1[1] = uVar5b;
        }
        uVar3 = FUN_0103b1e2(puVar6, 1, puVar4, uVar5b, param_1, param_2);
    }

    iVar2 = FUN_01036128(puVar7);
    if (iVar2 != 0) {
        if (isCurrentModePrivileged()) {
            setBasePriority((int)uVar8);
        }
        InstructionSynchronizationBarrier(0xf);
        return uVar3;
    }
    assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
    uVar8 = 0xf0;
    assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, uVar8);
    __builtin_unreachable();
}
