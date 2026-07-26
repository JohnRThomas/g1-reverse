/* net-core FUN_0102ec10 @ 0x102ec10  (parity 300 trials PROVEN) */
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

#define BASE G1_NET_K(0x00)
#define LITP 0x0103cb30u
#define SCB  0xe000ed00u

unsigned int FUN_0102ec10(unsigned int param_1)
{
    unsigned int iVar4 = *(volatile unsigned int *)(BASE + 8);
    unsigned int uVar3 = *(volatile unsigned int *)LITP;

    *(volatile unsigned int *)(iVar4 + 0x8c) = param_1;
    *(volatile unsigned int *)(iVar4 + 0x90) = uVar3;
    *(volatile unsigned int *)(SCB + 4) = *(volatile unsigned int *)(SCB + 4) | 0x10000000;
    __set_BASEPRI(0);
    __ISB();
    return *(volatile unsigned int *)(*(volatile unsigned int *)(BASE + 8) + 0x90);
}
