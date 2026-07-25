#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01037c64 @ 0x01037c64
 * public-name: FUN_01037c64
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103eb0e                           @ 0x0103eb0e
 */
/* net-core FUN_01037c64 @ 0x1037c64  (parity 300 trials PROVEN) */
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
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern void assert_print(unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
extern void FUN_01037768(unsigned int);
extern int FUN_01037b5c(void);

unsigned int FUN_01037c64(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int ipsr = __get_IPSR();
    if (ipsr != 0) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0x5c1, ipsr);
        assert_post_action(((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0x5c1);
    }
    unsigned int uVar3;
    if (param_2 == -1 && param_1 == -1) {
        volatile unsigned int * const dat = (volatile unsigned int *)G1_NET_K(0x00);
        FUN_01037768(*(unsigned int*)((char*)dat + 8));
        uVar3 = 0xffffffff;
    } else {
        int iVar2 = FUN_01037b5c();
        long long prod = (long long)iVar2 * 1000;
        uVar3 = (unsigned int)(((unsigned long long)prod) >> 0xf) |
                ((unsigned int)(((unsigned long long)prod) >> 0x20) << 0x11);
    }
    return uVar3;
}
