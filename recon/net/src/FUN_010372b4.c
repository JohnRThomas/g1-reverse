/* Zephyr k_sched_unlock @ 0x010372b4, exact executable extent 0x94.
 * Raw/address backmaps:
 *   FUN_010372b4@0x010372b4
 *   scheduler_lock@0x21004b68
 *   current_thread_slot@0x21004b30
 * Its terminal tail branch ends at 0x01037348, where literals begin.
 */
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
#define k_sched_unlock FUN_010372b4

extern int spin_validate(void *); /* FUN_0103610c */
extern void spin_lock(void *); /* FUN_01036144 */
extern int spin_unlock(void *); /* FUN_01036128 */
extern void update_cache(uint32_t); /* FUN_01036f74 */
extern void trace_sched_unlock(void); /* FUN_0103b2b4 */
extern void assert_print(uint32_t, uint32_t, uint32_t); /* FUN_01039bbe */
extern __attribute__((noreturn)) void
assert_post_action(uint32_t, uint32_t); /* FUN_01039bb0 */

void k_sched_unlock(void)
{
    void *lock = (void *)0x21004b68u;
    uint8_t *current;

    if (!spin_validate(lock)) {
        assert_print(0x0103d2a7u, 0x0103d3b6u, 0x72u);
        assert_post_action(0x0103d3b6u, 0x72u);
    }
    spin_lock(lock);
    current = *(uint8_t **)G1_NET_K(0x08);
    if (current[0x0f] == 0u) {
        assert_print(0x0103d2a7u, 0x0103eb0eu, 0x3f8u);
        assert_post_action(0x0103eb0eu, 0x3f8u);
    }
    if (__get_IPSR() != 0u) {
        assert_print(0x0103d2a7u, 0x0103eb0eu, 0x3f9u);
        assert_post_action(0x0103eb0eu, 0x3f9u);
    }
    ++current[0x0f];
    update_cache(0);
    if (!spin_unlock(lock)) {
        assert_print(0x0103d2a7u, 0x0103d3b6u, 0xf0u);
        assert_post_action(0x0103d3b6u, 0xf0u);
    }
    trace_sched_unlock();
}
