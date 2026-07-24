/* net-core FUN_01036128 @ 0x1036128  (parity 300 trials PROVEN) */


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

struct kernel_lock_state {
  unsigned int reserved[2];
  unsigned int owner;
  unsigned char padding[4];
  unsigned char nested;
};

int FUN_01036128(unsigned int *lock) {
  volatile struct kernel_lock_state *state =
      (volatile struct kernel_lock_state *)G1_NET_KERNEL_ADDR;
  unsigned int expected = state->owner | state->nested;
  int released = (*lock == expected);
  if (released) {
    *lock = 0;
  }
  return released;
}
