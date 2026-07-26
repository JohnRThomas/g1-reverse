/* net-core FUN_0102f580 @ 0x102f580 — true extent 36 bytes */
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

/* The final branch is the shared Zephyr thread-abort implementation at
   0x1037cc8; it is a tail call, not trailing code owned by this wrapper. */
extern void z_impl_k_thread_abort(void *thread);

void FUN_0102f580(void *thread)
{
    volatile uint32_t *const current_thread_slot =
        (volatile uint32_t *)G1_NET_K(0x08);
    volatile uint32_t *const scb = (volatile uint32_t *)0xe000ed00U;

    if (*current_thread_slot == (uint32_t)(uintptr_t)thread && __get_IPSR() != 0) {
        scb[1] |= 0x10000000U;       /* PendSV set */
        scb[0x24 / 4] &= ~0x8000U;   /* clear active exception bookkeeping */
    }
    z_impl_k_thread_abort(thread);
}
