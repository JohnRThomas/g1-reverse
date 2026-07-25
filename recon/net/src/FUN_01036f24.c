/* net-core FUN_01036f24 @ 0x1036f24  (parity 300 trials PROVEN) */

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

extern void FUN_010380d8(unsigned int a);
extern int FUN_01036e90(unsigned int a);
extern void FUN_01037f8c(unsigned int a, unsigned int b, int lo, int hi);

void FUN_01036f24(unsigned int param_1)
{
    unsigned char bVar1 = *(volatile unsigned char *)(G1_NET_K(0x00) + 0x10);
    unsigned int iVar3 = (unsigned int)bVar1 * 0x18 + 0x210044d8;
    int iVar2;
    int v;
    FUN_010380d8(iVar3);
    *(volatile unsigned char *)(0x21006462 + bVar1) = 0;
    iVar2 = FUN_01036e90(param_1);
    if (iVar2 != 0) {
        v = *(volatile int *)0x21004b64 - 1;
        FUN_01037f8c(iVar3, 0x010376cd, v, v >> 0x1f);
    }
}

