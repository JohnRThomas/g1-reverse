#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01037768 @ 0x01037768
 * public-name: FUN_01037768
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   g_zephyr_sched_thread_field              @ 0x21004b40
 */
/* net-core FUN_01037768 @ 0x1037768  (parity 300 trials PROVEN) */

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

#include <stdint.h>
#include <cmsis_gcc.h>

extern int FUN_0103610c(void *);
extern int FUN_01036128(void *);
extern void FUN_01036144(void *);
extern void FUN_01036f74(int);
extern void FUN_0103735c(unsigned int, int);
extern void FUN_010380d8(int);
extern void assert_post_action(unsigned int, unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int);
extern void FUN_0103b2b4(void);

void FUN_01037768(int param_1)
{
    FUN_010380d8(param_1 + 0x18);

    unsigned int uVar6 = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40u);
    __ISB();

    volatile int * const p1800 = (volatile int *)0x21004b68;
    int iVar4v = FUN_0103610c((void *)p1800);
    if (iVar4v == 0) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
        assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
        __builtin_unreachable();
    }

    FUN_01036144((void *)p1800);
    volatile signed char *pb = (volatile signed char *)param_1;
    if (pb[0xd] < 0) {
        ((volatile unsigned char *)param_1)[0xd] = ((volatile unsigned char *)param_1)[0xd] & 0x7f;
        FUN_0103735c(((unsigned long)&g_zephyr_sched_thread_field) /*=0x21004b40*/, param_1);
    }

    volatile int * const p1810 = (volatile int *)G1_NET_K(0x00);
    int iVar5 = p1810[2];
    ((volatile unsigned char *)param_1)[0xd] = ((volatile unsigned char *)param_1)[0xd] | 0x10;
    FUN_01036f74(iVar5 == param_1);

    int iVar5b = FUN_01036128((void *)p1800);
    if (iVar5b != 0) {
        __set_BASEPRI(uVar6);
        __ISB();
        if (p1810[2] != param_1) {
            return;
        }
        FUN_0103b2b4();
        return;
    }
    assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
    assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
    __builtin_unreachable();
}
