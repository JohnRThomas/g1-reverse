#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01036f74 @ 0x01036f74
 * public-name: FUN_01036f74
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103eb0e                           @ 0x0103eb0e
 */
/* net-core FUN_01036f74 @ 0x1036f74 */
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

extern void FUN_01036f24(void *node);
extern void assert_print(uintptr_t file, uintptr_t message, unsigned line, ...);
extern void assert_post_action(uintptr_t message, unsigned line);

void FUN_01036f74(int force_advance)
{
    uint8_t *state = (uint8_t *)G1_NET_K(0x00);
    uint8_t *head = *(uint8_t **)(state + 8);
    uint8_t *candidate = *(uint8_t **)(state + 0x18);

    if (candidate == state + 0x18 || candidate == 0)
        candidate = *(uint8_t **)(state + 0x0c);

    if (force_advance == 0) {
        if (head == 0) {
            assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0x8f, 0);
            assert_post_action(((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0x8f);
        }
        if ((head[0x0d] & 0x1f) == 0 &&
            *(uint32_t *)(candidate + 0x18) == 0 &&
            *(uint16_t *)(head + 0x0e) > 0x7f) {
            *(uint8_t **)(state + 0x14) = head;
            return;
        }
    }

    if (candidate != head)
        FUN_01036f24(candidate);
    *(uint8_t **)(state + 0x14) = candidate;
}
