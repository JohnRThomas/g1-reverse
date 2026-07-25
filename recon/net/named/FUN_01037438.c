/* readable reconstruction; identity: FUN_01037438 @ 0x01037438
 * public-name: FUN_01037438
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   g_net_ipc_shm_pool_desc_ptr              @ 0x21004b30
 *   g_21004b38                               @ 0x21004b38
 *   g_zephyr_sched_swap_tmp                  @ 0x21004b5c
 */
/* Zephyr z_reschedule_unlocked @ 0x01037438, exact extent 0x8a.
 * Raw/address backmaps:
 *   FUN_01037438@0x01037438
 *   scheduler_lock@0x21004b68
 *   current_thread_slot@0x21004b30
 *   ready_cache@0x21004b5c
 * The final return ends at 0x010374c2; alignment/literals follow.
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
#define z_reschedule_unlocked FUN_01037438

extern int spin_validate(void *); /* FUN_0103610c */
extern void spin_lock(void *); /* FUN_01036144 */
extern int spin_unlock(void *); /* FUN_01036128 */
extern void swap_current(uint8_t *); /* FUN_01036f24 */
extern int thread_can_swap(uint8_t *); /* FUN_01036e90 */
extern void prepare_thread_swap(uint8_t *); /* FUN_01037398 */
extern void assert_print(uint32_t, uint32_t, uint32_t); /* FUN_01039bbe */
extern __attribute__((noreturn)) void
assert_post_action(uint32_t, uint32_t); /* FUN_01039bb0 */

void z_reschedule_unlocked(void)
{
    void *lock = (void *)0x21004b68u;
    uint8_t *current;
    uint8_t *cached;

    if (!spin_validate(lock)) {
        assert_print(0x0103d2a7u, 0x0103d3b6u, 0x72u);
        assert_post_action(0x0103d3b6u, 0x72u);
    }
    spin_lock(lock);
    current = *(uint8_t **)G1_NET_K(0x08);
    cached = *(uint8_t **)0x21004b5cu;

    if (cached == current) {
        swap_current(current);
    } else {
        *(uint32_t *)0x21004b5cu = 0;
        uint8_t cpu = *(uint8_t *)G1_NET_K(0x10);

        if (*(uint8_t *)(0x21006462u + cpu) != 0u &&
            thread_can_swap(current)) {
            if ((current[0x0d] & 0x10u) == 0u) {
                prepare_thread_swap(current);
            }
            swap_current(current);
        }
    }
    if (!spin_unlock(lock)) {
        assert_print(0x0103d2a7u, 0x0103d3b6u, 0xf0u);
        assert_post_action(0x0103d3b6u, 0xf0u);
    }
}
