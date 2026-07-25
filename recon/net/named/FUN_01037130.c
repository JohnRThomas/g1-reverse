/* readable reconstruction; identity: FUN_01037130 @ 0x01037130
 * public-name: FUN_01037130
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* net-core FUN_01037130 @ 0x1037130  (parity 300 trials PROVEN) */
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

extern int FUN_01036128(int a);
extern void FUN_0102ec10(int a);
extern void assert_post_action(int a, int b);
extern void assert_print(int a, int b, int c);

static inline unsigned int read_ipsr(void)
{
    return 0;
}

static inline void write_basepri(unsigned int v)
{
    (void)v;
}

static inline void isb_sy(void)
{
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
}

void FUN_01037130(unsigned int param_1, unsigned int param_2)
{
    unsigned int r5 = 0;
    int r1val;

    if (param_2 == 0) {
        r5 = read_ipsr();
        if (r5 == 0) {
            unsigned int *base = (unsigned int *)G1_NET_K(0x00);
            unsigned int a = *(volatile unsigned int *)((char *)base + 0x14);
            unsigned int b = *(volatile unsigned int *)((char *)base + 8);
            if (a != b) {
                int iVar2 = FUN_01036128((int)param_1);
                if (iVar2 != 0) {
                    FUN_0102ec10((int)r5);
                    return;
                }
                assert_print(0x103d2a7, 0x103d3b6, 0x111);
                r1val = 0x111;
                assert_post_action(0x103d3b6, r1val);
                FUN_0102ec10((int)r5);
                return;
            }
        }
    }

    int iVar2b = FUN_01036128((int)param_1);
    if (iVar2b != 0) {
        write_basepri(param_2);
        isb_sy();
        return;
    }
    assert_print(0x103d2a7, 0x103d3b6, 0xf0);
    r1val = 0xf0;
    assert_post_action(0x103d3b6, r1val);
    FUN_0102ec10((int)r5);
}
