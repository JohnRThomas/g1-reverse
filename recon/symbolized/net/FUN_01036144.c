#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01036144 @ 0x01036144
 * public-name: FUN_01036144
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01036144 @ 0x1036144  (parity 300 trials PROVEN) */


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

static volatile unsigned char * const DAT_01036150 = (volatile unsigned char *)G1_NET_KERNEL_ADDR;
void FUN_01036144(unsigned int *param_1)
{
  unsigned int a = *(volatile unsigned int *)(DAT_01036150 + 8);
  unsigned int b = DAT_01036150[0x10];
  *param_1 = a | b;
}
