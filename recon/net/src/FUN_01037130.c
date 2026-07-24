/* net-core FUN_01037130 @ 0x1037130  (parity 300 trials PROVEN) */

#ifdef G1_COHESIVE_BUILD
/* P4 iteration 7 — relocate the CPUNET `_kernel` base.
 * 0x21004b28 is `_kernel` in the SHIPPED netcore image (the recovered spinlock
 * validators read _kernel.cpus[0].current at +8 and .id at +0x10, exactly like
 * Zephyr's own z_spin_lock_valid / z_spin_lock_set_owner / z_spin_unlock_valid).
 * Our net build puts _kernel at a different address (0x210083d0 in
 * /private/tmp/g1-i7b-net), and 0x21004b28 lands inside `sdc_mempool`, so the
 * recovered validators stamped a garbage owner into every spinlock they took.
 * MEASURED: FUN_0103689c (recovered k_sem_take) set the owner with the fake
 * _kernel and then tail-called the SDK's z_pend_curr, whose k_spin_release()
 * compares against the REAL _current -> "Not my spinlock"
 * (zephyr/include/zephyr/spinlock.h:273) -> kernel panic -> SYSRESETREQ.
 * Parity builds keep the original literal, so no parity body changes. */
#include <zephyr/kernel.h>
#include <zephyr/kernel_structs.h>
#define G1_NET_KERNEL_ADDR ((unsigned long)&_kernel)
#else
#define G1_NET_KERNEL_ADDR 0x21004b28u
#endif

extern int FUN_01036128(int a);
extern void FUN_0102ec10(int a);
extern void FUN_01039bb0(int a, int b);
extern void FUN_01039bbe(int a, int b, int c);

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
            unsigned int *base = (unsigned int *)G1_NET_KERNEL_ADDR;
            unsigned int a = *(volatile unsigned int *)((char *)base + 0x14);
            unsigned int b = *(volatile unsigned int *)((char *)base + 8);
            if (a != b) {
                int iVar2 = FUN_01036128((int)param_1);
                if (iVar2 != 0) {
                    FUN_0102ec10((int)r5);
                    return;
                }
                FUN_01039bbe(0x103d2a7, 0x103d3b6, 0x111);
                r1val = 0x111;
                FUN_01039bb0(0x103d3b6, r1val);
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
    FUN_01039bbe(0x103d2a7, 0x103d3b6, 0xf0);
    r1val = 0xf0;
    FUN_01039bb0(0x103d3b6, r1val);
    FUN_0102ec10((int)r5);
}

