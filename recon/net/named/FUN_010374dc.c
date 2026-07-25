/* readable reconstruction; identity: FUN_010374dc @ 0x010374dc
 * public-name: FUN_010374dc
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ipc_shm_pool_desc_ptr              @ 0x21004b30
 *   g_zephyr_sched_thread_field              @ 0x21004b40
 */
/* FUN_010374dc @ 0x010374dc: remove a queued node and advance the head. */
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

extern void FUN_0103735c(uintptr_t list, void *node);
extern void FUN_01036f74(int force_advance);

void FUN_010374dc(uint8_t *node)
{
    if ((int8_t)node[0x0d] < 0) {
        node[0x0d] &= 0x7f;
        FUN_0103735c(G1_NET_K(0x18), node);
    }

    FUN_01036f74(*(uint8_t **)G1_NET_K(0x08) == node);
}
